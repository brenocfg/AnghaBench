#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u32 ;
struct nfs_pgio_mirror {int /*<<< orphan*/  pg_recoalesce; } ;
struct nfs_pageio_descriptor {size_t pg_mirror_idx; scalar_t__ pg_error; struct nfs_pgio_mirror* pg_mirrors; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_do_recoalesce (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/  nfs_pageio_doio (struct nfs_pageio_descriptor*) ; 
 scalar_t__ nfs_pgio_has_mirroring (struct nfs_pageio_descriptor*) ; 

__attribute__((used)) static void nfs_pageio_complete_mirror(struct nfs_pageio_descriptor *desc,
				       u32 mirror_idx)
{
	struct nfs_pgio_mirror *mirror = &desc->pg_mirrors[mirror_idx];
	u32 restore_idx = desc->pg_mirror_idx;

	if (nfs_pgio_has_mirroring(desc))
		desc->pg_mirror_idx = mirror_idx;
	for (;;) {
		nfs_pageio_doio(desc);
		if (desc->pg_error < 0 || !mirror->pg_recoalesce)
			break;
		if (!nfs_do_recoalesce(desc))
			break;
	}
	desc->pg_mirror_idx = restore_idx;
}