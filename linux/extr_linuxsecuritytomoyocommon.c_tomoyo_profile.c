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
typedef  size_t u8 ;
struct tomoyo_profile {int dummy; } ;
struct tomoyo_policy_namespace {struct tomoyo_profile** profile_ptr; } ;

/* Variables and functions */

struct tomoyo_profile *tomoyo_profile(const struct tomoyo_policy_namespace *ns,
				      const u8 profile)
{
	static struct tomoyo_profile tomoyo_null_profile;
	struct tomoyo_profile *ptr = ns->profile_ptr[profile];
	if (!ptr)
		ptr = &tomoyo_null_profile;
	return ptr;
}