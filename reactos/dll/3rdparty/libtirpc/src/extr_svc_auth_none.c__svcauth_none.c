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
struct svc_req {TYPE_1__* rq_xprt; } ;
struct rpc_msg {int dummy; } ;
typedef  enum auth_stat { ____Placeholder_auth_stat } auth_stat ;
struct TYPE_2__ {int /*<<< orphan*/ * xp_auth; } ;

/* Variables and functions */
 int AUTH_OK ; 
 int /*<<< orphan*/  svc_auth_none ; 

enum auth_stat
_svcauth_none(struct svc_req *rqst, struct rpc_msg *msg)
{
	rqst->rq_xprt->xp_auth = &svc_auth_none;

	return (AUTH_OK);
}