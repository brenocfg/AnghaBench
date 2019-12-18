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
typedef  int u32 ;
struct aa_ns {int dummy; } ;
struct aa_label {int dummy; } ;

/* Variables and functions */
 int AA_MAY_REMOVE_POLICY ; 
 int AA_MAY_REPLACE_POLICY ; 
 int /*<<< orphan*/  EACCES ; 
 char* OP_PROF_LOAD ; 
 char* OP_PROF_REPL ; 
 char* OP_PROF_RM ; 
 scalar_t__ aa_g_lock_policy ; 
 int audit_policy (struct aa_label*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_admin_capable (struct aa_ns*) ; 

int aa_may_manage_policy(struct aa_label *label, struct aa_ns *ns, u32 mask)
{
	const char *op;

	if (mask & AA_MAY_REMOVE_POLICY)
		op = OP_PROF_RM;
	else if (mask & AA_MAY_REPLACE_POLICY)
		op = OP_PROF_REPL;
	else
		op = OP_PROF_LOAD;

	/* check if loading policy is locked out */
	if (aa_g_lock_policy)
		return audit_policy(label, op, NULL, NULL, "policy_locked",
				    -EACCES);

	if (!policy_admin_capable(ns))
		return audit_policy(label, op, NULL, NULL, "not policy admin",
				    -EACCES);

	/* TODO: add fine grained mediation of policy loads */
	return 0;
}