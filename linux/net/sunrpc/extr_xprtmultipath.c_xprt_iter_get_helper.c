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
struct rpc_xprt {int dummy; } ;

/* Variables and functions */
 struct rpc_xprt* xprt_get (struct rpc_xprt*) ; 

__attribute__((used)) static
struct rpc_xprt *xprt_iter_get_helper(struct rpc_xprt_iter *xpi,
		struct rpc_xprt *(*fn)(struct rpc_xprt_iter *))
{
	struct rpc_xprt *ret;

	do {
		ret = fn(xpi);
		if (ret == NULL)
			break;
		ret = xprt_get(ret);
	} while (ret == NULL);
	return ret;
}