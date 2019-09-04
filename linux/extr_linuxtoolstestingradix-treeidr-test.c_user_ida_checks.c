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

/* Variables and functions */
 int /*<<< orphan*/  ida_check_conv_user () ; 
 int /*<<< orphan*/  ida_check_nomem () ; 
 int /*<<< orphan*/  ida_check_random () ; 
 int /*<<< orphan*/  ida_simple_get_remove_test () ; 
 int /*<<< orphan*/  radix_tree_cpu_dead (int) ; 

void user_ida_checks(void)
{
	radix_tree_cpu_dead(1);

	ida_check_nomem();
	ida_check_conv_user();
	ida_check_random();
	ida_simple_get_remove_test();

	radix_tree_cpu_dead(1);
}