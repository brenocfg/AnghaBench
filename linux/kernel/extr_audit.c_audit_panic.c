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
#define  AUDIT_FAIL_PANIC 130 
#define  AUDIT_FAIL_PRINTK 129 
#define  AUDIT_FAIL_SILENT 128 
 int audit_failure ; 
 int /*<<< orphan*/  panic (char*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  printk_ratelimit () ; 

void audit_panic(const char *message)
{
	switch (audit_failure) {
	case AUDIT_FAIL_SILENT:
		break;
	case AUDIT_FAIL_PRINTK:
		if (printk_ratelimit())
			pr_err("%s\n", message);
		break;
	case AUDIT_FAIL_PANIC:
		panic("audit: %s\n", message);
		break;
	}
}