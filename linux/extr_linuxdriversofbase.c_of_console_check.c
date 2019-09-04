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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_preferred_console (char*,int,char*) ; 
 scalar_t__ console_set_on_cmdline ; 
 struct device_node* of_stdout ; 
 scalar_t__ of_stdout_options ; 

bool of_console_check(struct device_node *dn, char *name, int index)
{
	if (!dn || dn != of_stdout || console_set_on_cmdline)
		return false;

	/*
	 * XXX: cast `options' to char pointer to suppress complication
	 * warnings: printk, UART and console drivers expect char pointer.
	 */
	return !add_preferred_console(name, index, (char *)of_stdout_options);
}