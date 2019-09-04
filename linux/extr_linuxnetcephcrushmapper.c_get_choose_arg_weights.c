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
struct crush_choose_arg {int weight_set_size; TYPE_1__* weight_set; } ;
struct crush_bucket_straw2 {int /*<<< orphan*/ * item_weights; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * weights; } ;

/* Variables and functions */

__attribute__((used)) static __u32 *get_choose_arg_weights(const struct crush_bucket_straw2 *bucket,
				     const struct crush_choose_arg *arg,
				     int position)
{
	if (!arg || !arg->weight_set)
		return bucket->item_weights;

	if (position >= arg->weight_set_size)
		position = arg->weight_set_size - 1;
	return arg->weight_set[position].weights;
}