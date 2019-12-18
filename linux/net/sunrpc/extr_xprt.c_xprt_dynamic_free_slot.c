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
struct rpc_xprt {scalar_t__ num_reqs; scalar_t__ min_reqs; } ;
struct rpc_rqst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rpc_rqst*) ; 

__attribute__((used)) static bool xprt_dynamic_free_slot(struct rpc_xprt *xprt, struct rpc_rqst *req)
{
	if (xprt->num_reqs > xprt->min_reqs) {
		--xprt->num_reqs;
		kfree(req);
		return true;
	}
	return false;
}