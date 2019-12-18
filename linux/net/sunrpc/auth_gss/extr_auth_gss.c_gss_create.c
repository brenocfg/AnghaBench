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
struct rpc_xprt_switch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xpi_xpswitch; } ;
struct rpc_clnt {TYPE_1__ cl_xpi; struct rpc_clnt* cl_parent; } ;
struct rpc_auth_create_args {int dummy; } ;
struct rpc_auth {int dummy; } ;
struct gss_auth {struct rpc_auth rpc_auth; } ;

/* Variables and functions */
 struct rpc_auth* ERR_CAST (struct gss_auth*) ; 
 scalar_t__ IS_ERR (struct gss_auth*) ; 
 struct gss_auth* gss_create_hashed (struct rpc_auth_create_args const*,struct rpc_clnt*) ; 
 struct rpc_xprt_switch* rcu_access_pointer (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rpc_auth *
gss_create(const struct rpc_auth_create_args *args, struct rpc_clnt *clnt)
{
	struct gss_auth *gss_auth;
	struct rpc_xprt_switch *xps = rcu_access_pointer(clnt->cl_xpi.xpi_xpswitch);

	while (clnt != clnt->cl_parent) {
		struct rpc_clnt *parent = clnt->cl_parent;
		/* Find the original parent for this transport */
		if (rcu_access_pointer(parent->cl_xpi.xpi_xpswitch) != xps)
			break;
		clnt = parent;
	}

	gss_auth = gss_create_hashed(args, clnt);
	if (IS_ERR(gss_auth))
		return ERR_CAST(gss_auth);
	return &gss_auth->rpc_auth;
}