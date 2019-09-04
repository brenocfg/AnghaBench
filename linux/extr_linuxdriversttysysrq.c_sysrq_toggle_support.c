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
 int sysrq_enabled ; 
 int sysrq_on () ; 
 int /*<<< orphan*/  sysrq_register_handler () ; 
 int /*<<< orphan*/  sysrq_unregister_handler () ; 

int sysrq_toggle_support(int enable_mask)
{
	bool was_enabled = sysrq_on();

	sysrq_enabled = enable_mask;

	if (was_enabled != sysrq_on()) {
		if (sysrq_on())
			sysrq_register_handler();
		else
			sysrq_unregister_handler();
	}

	return 0;
}