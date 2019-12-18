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
struct kparam_string {scalar_t__ maxlen; int /*<<< orphan*/  string; } ;
struct kernel_param {int /*<<< orphan*/  name; struct kparam_string* str; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int param_set_copystring(const char *val, const struct kernel_param *kp)
{
	const struct kparam_string *kps = kp->str;

	if (strlen(val)+1 > kps->maxlen) {
		pr_err("%s: string doesn't fit in %u chars.\n",
		       kp->name, kps->maxlen-1);
		return -ENOSPC;
	}
	strcpy(kps->string, val);
	return 0;
}