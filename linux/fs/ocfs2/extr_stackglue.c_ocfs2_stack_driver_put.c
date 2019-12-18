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
struct TYPE_2__ {scalar_t__ sp_count; int /*<<< orphan*/  sp_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_1__* active_stack ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_stack_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_stack_driver_put(void)
{
	spin_lock(&ocfs2_stack_lock);
	BUG_ON(active_stack == NULL);
	BUG_ON(active_stack->sp_count == 0);

	active_stack->sp_count--;
	if (!active_stack->sp_count) {
		module_put(active_stack->sp_owner);
		active_stack = NULL;
	}
	spin_unlock(&ocfs2_stack_lock);
}