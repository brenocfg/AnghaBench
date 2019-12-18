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
struct rpc_xprt {scalar_t__ num_reqs; scalar_t__ max_reqs; int /*<<< orphan*/  reserve_lock; } ;
struct rpc_rqst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct rpc_rqst* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct rpc_rqst* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rpc_rqst *xprt_dynamic_alloc_slot(struct rpc_xprt *xprt)
{
	struct rpc_rqst *req = ERR_PTR(-EAGAIN);

	if (xprt->num_reqs >= xprt->max_reqs)
		goto out;
	++xprt->num_reqs;
	spin_unlock(&xprt->reserve_lock);
	req = kzalloc(sizeof(struct rpc_rqst), GFP_NOFS);
	spin_lock(&xprt->reserve_lock);
	if (req != NULL)
		goto out;
	--xprt->num_reqs;
	req = ERR_PTR(-ENOMEM);
out:
	return req;
}