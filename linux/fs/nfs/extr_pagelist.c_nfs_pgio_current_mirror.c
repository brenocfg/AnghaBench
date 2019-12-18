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
struct nfs_pgio_mirror {int dummy; } ;
struct nfs_pageio_descriptor {size_t pg_mirror_idx; struct nfs_pgio_mirror* pg_mirrors; } ;

/* Variables and functions */
 scalar_t__ nfs_pgio_has_mirroring (struct nfs_pageio_descriptor*) ; 

struct nfs_pgio_mirror *
nfs_pgio_current_mirror(struct nfs_pageio_descriptor *desc)
{
	return nfs_pgio_has_mirroring(desc) ?
		&desc->pg_mirrors[desc->pg_mirror_idx] :
		&desc->pg_mirrors[0];
}