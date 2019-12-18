#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dsaddr; } ;
struct TYPE_3__ {size_t* stripe_indices; } ;

/* Variables and functions */
 TYPE_2__* FILELAYOUT_LSEG (struct pnfs_layout_segment*) ; 

u32
nfs4_fl_calc_ds_index(struct pnfs_layout_segment *lseg, u32 j)
{
	return FILELAYOUT_LSEG(lseg)->dsaddr->stripe_indices[j];
}