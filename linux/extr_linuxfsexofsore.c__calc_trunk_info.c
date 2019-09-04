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
typedef  int /*<<< orphan*/  u64 ;
struct ore_layout {unsigned int stripe_unit; int group_width; } ;
struct TYPE_2__ {unsigned int M; int dev; } ;
struct _trunc_info {unsigned int prev_group_obj_off; int next_group_obj_off; int first_group_dev; int nex_group_dev; TYPE_1__ si; } ;

/* Variables and functions */
 int /*<<< orphan*/  ore_calc_stripe_info (struct ore_layout*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void _calc_trunk_info(struct ore_layout *layout, u64 file_offset,
			     struct _trunc_info *ti)
{
	unsigned stripe_unit = layout->stripe_unit;

	ore_calc_stripe_info(layout, file_offset, 0, &ti->si);

	ti->prev_group_obj_off = ti->si.M * stripe_unit;
	ti->next_group_obj_off = ti->si.M ? (ti->si.M - 1) * stripe_unit : 0;

	ti->first_group_dev = ti->si.dev - (ti->si.dev % layout->group_width);
	ti->nex_group_dev = ti->first_group_dev + layout->group_width;
}