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
typedef  int /*<<< orphan*/  uint8_t ;
struct obs_scene_item {int /*<<< orphan*/  parent; } ;
struct calldata {int dummy; } ;
typedef  int /*<<< orphan*/  stack ;

/* Variables and functions */
 int /*<<< orphan*/  calldata_init_fixed (struct calldata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  calldata_set_ptr (struct calldata*,char*,struct obs_scene_item*) ; 
 int /*<<< orphan*/  signal_parent (int /*<<< orphan*/ ,char*,struct calldata*) ; 

__attribute__((used)) static inline void signal_item_remove(struct obs_scene_item *item)
{
	struct calldata params;
	uint8_t stack[128];

	calldata_init_fixed(&params, stack, sizeof(stack));
	calldata_set_ptr(&params, "item", item);

	signal_parent(item->parent, "item_remove", &params);
}