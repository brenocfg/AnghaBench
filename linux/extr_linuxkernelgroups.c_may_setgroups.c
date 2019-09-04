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
 int /*<<< orphan*/  CAP_SETGID ; 
 struct user_namespace* current_user_ns () ; 
 scalar_t__ ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ userns_may_setgroups (struct user_namespace*) ; 

bool may_setgroups(void)
{
	struct user_namespace *user_ns = current_user_ns();

	return ns_capable(user_ns, CAP_SETGID) &&
		userns_may_setgroups(user_ns);
}