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
struct rpc_xprt_switch {int /*<<< orphan*/ * xps_iter_ops; int /*<<< orphan*/  xps_xprt_list; int /*<<< orphan*/ * xps_net; int /*<<< orphan*/  xps_queuelen; scalar_t__ xps_nactive; scalar_t__ xps_nxprts; int /*<<< orphan*/  xps_kref; int /*<<< orphan*/  xps_lock; } ;
struct rpc_xprt {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rpc_xprt_switch* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_xprt_iter_singular ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xprt_switch_add_xprt_locked (struct rpc_xprt_switch*,struct rpc_xprt*) ; 

struct rpc_xprt_switch *xprt_switch_alloc(struct rpc_xprt *xprt,
		gfp_t gfp_flags)
{
	struct rpc_xprt_switch *xps;

	xps = kmalloc(sizeof(*xps), gfp_flags);
	if (xps != NULL) {
		spin_lock_init(&xps->xps_lock);
		kref_init(&xps->xps_kref);
		xps->xps_nxprts = xps->xps_nactive = 0;
		atomic_long_set(&xps->xps_queuelen, 0);
		xps->xps_net = NULL;
		INIT_LIST_HEAD(&xps->xps_xprt_list);
		xps->xps_iter_ops = &rpc_xprt_iter_singular;
		xprt_switch_add_xprt_locked(xps, xprt);
	}

	return xps;
}