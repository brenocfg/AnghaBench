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
struct kernel_param {scalar_t__ arg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 char* kmalloc_parameter (int) ; 
 int /*<<< orphan*/  maybe_kfree_parameter (char*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ slab_is_available () ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

int param_set_charp(const char *val, const struct kernel_param *kp)
{
	if (strlen(val) > 1024) {
		pr_err("%s: string parameter too long\n", kp->name);
		return -ENOSPC;
	}

	maybe_kfree_parameter(*(char **)kp->arg);

	/* This is a hack.  We can't kmalloc in early boot, and we
	 * don't need to; this mangled commandline is preserved. */
	if (slab_is_available()) {
		*(char **)kp->arg = kmalloc_parameter(strlen(val)+1);
		if (!*(char **)kp->arg)
			return -ENOMEM;
		strcpy(*(char **)kp->arg, val);
	} else
		*(const char **)kp->arg = val;

	return 0;
}