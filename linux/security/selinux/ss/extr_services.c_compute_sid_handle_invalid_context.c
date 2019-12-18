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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct selinux_state {TYPE_1__* ss; } ;
struct policydb {int dummy; } ;
struct context {int dummy; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_2__ {struct policydb policydb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SELINUX_ERR ; 
 int EACCES ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SYM_CLASSES ; 
 int /*<<< orphan*/  audit_context () ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_n_untrustedstring (struct audit_buffer*,char*,scalar_t__) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ context_struct_to_string (struct policydb*,struct context*,char**,scalar_t__*) ; 
 int /*<<< orphan*/  enforcing_enabled (struct selinux_state*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  sym_name (struct policydb*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int compute_sid_handle_invalid_context(
	struct selinux_state *state,
	struct context *scontext,
	struct context *tcontext,
	u16 tclass,
	struct context *newcontext)
{
	struct policydb *policydb = &state->ss->policydb;
	char *s = NULL, *t = NULL, *n = NULL;
	u32 slen, tlen, nlen;
	struct audit_buffer *ab;

	if (context_struct_to_string(policydb, scontext, &s, &slen))
		goto out;
	if (context_struct_to_string(policydb, tcontext, &t, &tlen))
		goto out;
	if (context_struct_to_string(policydb, newcontext, &n, &nlen))
		goto out;
	ab = audit_log_start(audit_context(), GFP_ATOMIC, AUDIT_SELINUX_ERR);
	audit_log_format(ab,
			 "op=security_compute_sid invalid_context=");
	/* no need to record the NUL with untrusted strings */
	audit_log_n_untrustedstring(ab, n, nlen - 1);
	audit_log_format(ab, " scontext=%s tcontext=%s tclass=%s",
			 s, t, sym_name(policydb, SYM_CLASSES, tclass-1));
	audit_log_end(ab);
out:
	kfree(s);
	kfree(t);
	kfree(n);
	if (!enforcing_enabled(state))
		return 0;
	return -EACCES;
}