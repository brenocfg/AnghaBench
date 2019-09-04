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
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_ff_layout_mirror {int dummy; } ;
struct TYPE_2__ {size_t mirror_array_cnt; struct nfs4_ff_layout_mirror** mirror_array; } ;

/* Variables and functions */
 TYPE_1__* FF_LAYOUT_LSEG (struct pnfs_layout_segment*) ; 

__attribute__((used)) static inline struct nfs4_ff_layout_mirror *
FF_LAYOUT_COMP(struct pnfs_layout_segment *lseg, u32 idx)
{
	if (idx >= FF_LAYOUT_LSEG(lseg)->mirror_array_cnt)
		return NULL;
	return FF_LAYOUT_LSEG(lseg)->mirror_array[idx];
}