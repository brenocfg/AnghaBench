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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pnfs_layout_segment {int dummy; } ;
struct nfs4_filelayout_segment {TYPE_1__* dsaddr; scalar_t__ first_stripe_index; int /*<<< orphan*/  stripe_unit; scalar_t__ pattern_offset; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  stripe_count; } ;

/* Variables and functions */
 struct nfs4_filelayout_segment* FILELAYOUT_LSEG (struct pnfs_layout_segment*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 

u32
nfs4_fl_calc_j_index(struct pnfs_layout_segment *lseg, loff_t offset)
{
	struct nfs4_filelayout_segment *flseg = FILELAYOUT_LSEG(lseg);
	u64 tmp;

	tmp = offset - flseg->pattern_offset;
	do_div(tmp, flseg->stripe_unit);
	tmp += flseg->first_stripe_index;
	return do_div(tmp, flseg->dsaddr->stripe_count);
}