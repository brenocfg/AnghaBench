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
struct rpc_cred {struct rpc_auth* cr_auth; } ;
struct rpc_auth {int /*<<< orphan*/  au_verfsize; int /*<<< orphan*/  au_ralign; int /*<<< orphan*/  au_rslack; } ;

/* Variables and functions */

__attribute__((used)) static int
gss_unwrap_resp_auth(struct rpc_cred *cred)
{
	struct rpc_auth *auth = cred->cr_auth;

	auth->au_rslack = auth->au_verfsize;
	auth->au_ralign = auth->au_verfsize;
	return 0;
}