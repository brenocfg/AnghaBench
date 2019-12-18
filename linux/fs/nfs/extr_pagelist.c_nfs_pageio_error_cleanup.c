#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct nfs_pgio_mirror {int /*<<< orphan*/  pg_list; } ;
struct nfs_pageio_descriptor {size_t pg_mirror_count; int /*<<< orphan*/  pg_error; TYPE_1__* pg_completion_ops; struct nfs_pgio_mirror* pg_mirrors; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* error_cleanup ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfs_pageio_error_cleanup(struct nfs_pageio_descriptor *desc)
{
	u32 midx;
	struct nfs_pgio_mirror *mirror;

	if (!desc->pg_error)
		return;

	for (midx = 0; midx < desc->pg_mirror_count; midx++) {
		mirror = &desc->pg_mirrors[midx];
		desc->pg_completion_ops->error_cleanup(&mirror->pg_list,
				desc->pg_error);
	}
}