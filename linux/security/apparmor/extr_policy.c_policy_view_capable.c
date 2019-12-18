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
struct user_namespace {scalar_t__ level; } ;
struct aa_ns {scalar_t__ level; } ;

/* Variables and functions */
 struct aa_ns* aa_get_current_ns () ; 
 scalar_t__ aa_ns_visible (struct aa_ns*,struct aa_ns*,int) ; 
 int /*<<< orphan*/  aa_put_ns (struct aa_ns*) ; 
 int /*<<< orphan*/  current_euid () ; 
 struct user_namespace* current_user_ns () ; 
 scalar_t__ in_egroup_p (int /*<<< orphan*/ ) ; 
 struct user_namespace init_user_ns ; 
 int /*<<< orphan*/  make_kgid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unprivileged_userns_apparmor_policy ; 

bool policy_view_capable(struct aa_ns *ns)
{
	struct user_namespace *user_ns = current_user_ns();
	struct aa_ns *view_ns = aa_get_current_ns();
	bool root_in_user_ns = uid_eq(current_euid(), make_kuid(user_ns, 0)) ||
			       in_egroup_p(make_kgid(user_ns, 0));
	bool response = false;
	if (!ns)
		ns = view_ns;

	if (root_in_user_ns && aa_ns_visible(view_ns, ns, true) &&
	    (user_ns == &init_user_ns ||
	     (unprivileged_userns_apparmor_policy != 0 &&
	      user_ns->level == view_ns->level)))
		response = true;
	aa_put_ns(view_ns);

	return response;
}