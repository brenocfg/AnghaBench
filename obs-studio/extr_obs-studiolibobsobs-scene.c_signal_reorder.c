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
 int /*<<< orphan*/  signal_parent (int /*<<< orphan*/ ,char const*,struct calldata*) ; 

__attribute__((used)) static inline void signal_reorder(struct obs_scene_item *item)
{
	const char *command = NULL;
	struct calldata params;
	uint8_t stack[128];

	command = "reorder";

	calldata_init_fixed(&params, stack, sizeof(stack));
	signal_parent(item->parent, command, &params);
}