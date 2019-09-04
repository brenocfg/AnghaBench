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
struct user_namespace {int dummy; } ;

/* Variables and functions */
 struct user_namespace* current_user_ns () ; 
 struct user_namespace init_user_ns ; 
 int /*<<< orphan*/  posix_acl_fix_xattr_userns (struct user_namespace*,struct user_namespace*,void*,size_t) ; 

void posix_acl_fix_xattr_to_user(void *value, size_t size)
{
	struct user_namespace *user_ns = current_user_ns();
	if (user_ns == &init_user_ns)
		return;
	posix_acl_fix_xattr_userns(user_ns, &init_user_ns, value, size);
}