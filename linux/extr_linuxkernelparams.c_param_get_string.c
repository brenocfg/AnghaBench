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
struct kparam_string {int /*<<< orphan*/  string; } ;
struct kernel_param {struct kparam_string* str; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int param_get_string(char *buffer, const struct kernel_param *kp)
{
	const struct kparam_string *kps = kp->str;
	return scnprintf(buffer, PAGE_SIZE, "%s\n", kps->string);
}