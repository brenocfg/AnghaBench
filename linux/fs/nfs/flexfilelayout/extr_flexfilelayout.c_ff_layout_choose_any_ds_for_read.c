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
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_pnfs_ds {int dummy; } ;

/* Variables and functions */
 struct nfs4_pnfs_ds* ff_layout_choose_ds_for_read (struct pnfs_layout_segment*,int,int*,int) ; 

__attribute__((used)) static struct nfs4_pnfs_ds *
ff_layout_choose_any_ds_for_read(struct pnfs_layout_segment *lseg,
				 int start_idx, int *best_idx)
{
	return ff_layout_choose_ds_for_read(lseg, start_idx, best_idx, false);
}