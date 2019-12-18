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
struct rpc_clnt {int dummy; } ;
struct rpc_auth_create_args {int dummy; } ;
struct gss_auth {int /*<<< orphan*/  rpc_auth; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gss_auth*) ; 
 struct gss_auth* gss_auth_find_or_add_hashed (struct rpc_auth_create_args const*,struct rpc_clnt*,struct gss_auth*) ; 
 struct gss_auth* gss_create_new (struct rpc_auth_create_args const*,struct rpc_clnt*) ; 
 int /*<<< orphan*/  gss_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gss_auth *
gss_create_hashed(const struct rpc_auth_create_args *args,
		  struct rpc_clnt *clnt)
{
	struct gss_auth *gss_auth;
	struct gss_auth *new;

	gss_auth = gss_auth_find_or_add_hashed(args, clnt, NULL);
	if (gss_auth != NULL)
		goto out;
	new = gss_create_new(args, clnt);
	if (IS_ERR(new))
		return new;
	gss_auth = gss_auth_find_or_add_hashed(args, clnt, new);
	if (gss_auth != new)
		gss_destroy(&new->rpc_auth);
out:
	return gss_auth;
}