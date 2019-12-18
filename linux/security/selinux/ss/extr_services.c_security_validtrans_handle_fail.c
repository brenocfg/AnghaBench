#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct selinux_state {TYPE_1__* ss; } ;
struct policydb {int dummy; } ;
struct context {int dummy; } ;
struct TYPE_2__ {struct policydb policydb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SELINUX_ERR ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SYM_CLASSES ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ context_struct_to_string (struct policydb*,struct context*,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enforcing_enabled (struct selinux_state*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  sym_name (struct policydb*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int security_validtrans_handle_fail(struct selinux_state *state,
					   struct context *ocontext,
					   struct context *ncontext,
					   struct context *tcontext,
					   u16 tclass)
{
	struct policydb *p = &state->ss->policydb;
	char *o = NULL, *n = NULL, *t = NULL;
	u32 olen, nlen, tlen;

	if (context_struct_to_string(p, ocontext, &o, &olen))
		goto out;
	if (context_struct_to_string(p, ncontext, &n, &nlen))
		goto out;
	if (context_struct_to_string(p, tcontext, &t, &tlen))
		goto out;
	audit_log(audit_context(), GFP_ATOMIC, AUDIT_SELINUX_ERR,
		  "op=security_validate_transition seresult=denied"
		  " oldcontext=%s newcontext=%s taskcontext=%s tclass=%s",
		  o, n, t, sym_name(p, SYM_CLASSES, tclass-1));
out:
	kfree(o);
	kfree(n);
	kfree(t);

	if (!enforcing_enabled(state))
		return 0;
	return -EPERM;
}