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
struct TYPE_2__ {unsigned long cr_flags; int /*<<< orphan*/  cr_cred; } ;
struct gss_cred {int /*<<< orphan*/  gc_ctx; int /*<<< orphan*/  gc_principal; int /*<<< orphan*/  gc_service; TYPE_1__ gc_base; } ;
struct gss_cl_ctx {int dummy; } ;
struct gss_auth {int /*<<< orphan*/  kref; int /*<<< orphan*/  rpc_auth; } ;
struct auth_cred {int /*<<< orphan*/  cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned long RPCAUTH_CRED_UPTODATE ; 
 int /*<<< orphan*/  gss_get_ctx (struct gss_cl_ctx*) ; 
 int /*<<< orphan*/  gss_nullops ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 struct gss_cred* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct gss_cl_ctx*) ; 
 struct gss_cl_ctx* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rpcauth_init_cred (TYPE_1__*,struct auth_cred*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gss_cred *
gss_dup_cred(struct gss_auth *gss_auth, struct gss_cred *gss_cred)
{
	struct gss_cred *new;

	/* Make a copy of the cred so that we can reference count it */
	new = kzalloc(sizeof(*gss_cred), GFP_NOFS);
	if (new) {
		struct auth_cred acred = {
			.cred = gss_cred->gc_base.cr_cred,
		};
		struct gss_cl_ctx *ctx =
			rcu_dereference_protected(gss_cred->gc_ctx, 1);

		rpcauth_init_cred(&new->gc_base, &acred,
				&gss_auth->rpc_auth,
				&gss_nullops);
		new->gc_base.cr_flags = 1UL << RPCAUTH_CRED_UPTODATE;
		new->gc_service = gss_cred->gc_service;
		new->gc_principal = gss_cred->gc_principal;
		kref_get(&gss_auth->kref);
		rcu_assign_pointer(new->gc_ctx, ctx);
		gss_get_ctx(ctx);
	}
	return new;
}