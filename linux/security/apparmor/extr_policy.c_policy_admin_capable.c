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
struct aa_ns {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_DEBUG (char*,int) ; 
 int /*<<< orphan*/  CAP_MAC_ADMIN ; 
 int aa_g_lock_policy ; 
 struct user_namespace* current_user_ns () ; 
 int ns_capable (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ policy_view_capable (struct aa_ns*) ; 

bool policy_admin_capable(struct aa_ns *ns)
{
	struct user_namespace *user_ns = current_user_ns();
	bool capable = ns_capable(user_ns, CAP_MAC_ADMIN);

	AA_DEBUG("cap_mac_admin? %d\n", capable);
	AA_DEBUG("policy locked? %d\n", aa_g_lock_policy);

	return policy_view_capable(ns) && capable && !aa_g_lock_policy;
}