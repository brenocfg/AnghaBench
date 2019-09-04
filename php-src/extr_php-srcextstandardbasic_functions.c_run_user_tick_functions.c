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
typedef  int /*<<< orphan*/  llist_apply_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  BG (int /*<<< orphan*/ ) ; 
 scalar_t__ user_tick_function_call ; 
 int /*<<< orphan*/  user_tick_functions ; 
 int /*<<< orphan*/  zend_llist_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_user_tick_functions(int tick_count, void *arg) /* {{{ */
{
	zend_llist_apply(BG(user_tick_functions), (llist_apply_func_t) user_tick_function_call);
}