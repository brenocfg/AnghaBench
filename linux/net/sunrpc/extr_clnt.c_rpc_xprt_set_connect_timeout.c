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
struct rpc_xprt {TYPE_1__* ops; } ;
struct rpc_clnt {int dummy; } ;
struct connect_timeout_data {int /*<<< orphan*/  reconnect_timeout; int /*<<< orphan*/  connect_timeout; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_connect_timeout ) (struct rpc_xprt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_xprt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rpc_xprt_set_connect_timeout(struct rpc_clnt *clnt,
		struct rpc_xprt *xprt,
		void *data)
{
	struct connect_timeout_data *timeo = data;

	if (xprt->ops->set_connect_timeout)
		xprt->ops->set_connect_timeout(xprt,
				timeo->connect_timeout,
				timeo->reconnect_timeout);
	return 0;
}