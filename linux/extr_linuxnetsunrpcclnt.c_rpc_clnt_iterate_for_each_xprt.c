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
struct rpc_xprt_iter {int dummy; } ;
typedef  struct rpc_xprt rpc_xprt ;
struct rpc_clnt {int dummy; } ;

/* Variables and functions */
 int rpc_clnt_xprt_iter_init (struct rpc_clnt*,struct rpc_xprt_iter*) ; 
 int /*<<< orphan*/  xprt_iter_destroy (struct rpc_xprt_iter*) ; 
 struct rpc_xprt* xprt_iter_get_next (struct rpc_xprt_iter*) ; 
 int /*<<< orphan*/  xprt_put (struct rpc_xprt*) ; 

int rpc_clnt_iterate_for_each_xprt(struct rpc_clnt *clnt,
		int (*fn)(struct rpc_clnt *, struct rpc_xprt *, void *),
		void *data)
{
	struct rpc_xprt_iter xpi;
	int ret;

	ret = rpc_clnt_xprt_iter_init(clnt, &xpi);
	if (ret)
		return ret;
	for (;;) {
		struct rpc_xprt *xprt = xprt_iter_get_next(&xpi);

		if (!xprt)
			break;
		ret = fn(clnt, xprt, data);
		xprt_put(xprt);
		if (ret < 0)
			break;
	}
	xprt_iter_destroy(&xpi);
	return ret;
}