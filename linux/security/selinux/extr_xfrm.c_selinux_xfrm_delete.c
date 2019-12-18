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
struct xfrm_sec_ctx {int /*<<< orphan*/  ctx_sid; } ;
struct task_security_struct {int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCIATION__SETCONTEXT ; 
 int /*<<< orphan*/  SECCLASS_ASSOCIATION ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_cred () ; 
 struct task_security_struct* selinux_cred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selinux_state ; 

__attribute__((used)) static int selinux_xfrm_delete(struct xfrm_sec_ctx *ctx)
{
	const struct task_security_struct *tsec = selinux_cred(current_cred());

	if (!ctx)
		return 0;

	return avc_has_perm(&selinux_state,
			    tsec->sid, ctx->ctx_sid,
			    SECCLASS_ASSOCIATION, ASSOCIATION__SETCONTEXT,
			    NULL);
}