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
struct rpc_xprt {int dummy; } ;
struct rpc_rqst {scalar_t__ rq_connect_cookie; } ;

/* Variables and functions */
 scalar_t__ xprt_connect_cookie (struct rpc_xprt*) ; 

__attribute__((used)) static void
xprt_init_connect_cookie(struct rpc_rqst *req, struct rpc_xprt *xprt)
{
	req->rq_connect_cookie = xprt_connect_cookie(xprt) - 1;
}