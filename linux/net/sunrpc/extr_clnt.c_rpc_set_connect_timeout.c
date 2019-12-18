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
struct connect_timeout_data {unsigned long connect_timeout; unsigned long reconnect_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_clnt_iterate_for_each_xprt (struct rpc_clnt*,int /*<<< orphan*/ ,struct connect_timeout_data*) ; 
 int /*<<< orphan*/  rpc_xprt_set_connect_timeout ; 

void
rpc_set_connect_timeout(struct rpc_clnt *clnt,
		unsigned long connect_timeout,
		unsigned long reconnect_timeout)
{
	struct connect_timeout_data timeout = {
		.connect_timeout = connect_timeout,
		.reconnect_timeout = reconnect_timeout,
	};
	rpc_clnt_iterate_for_each_xprt(clnt,
			rpc_xprt_set_connect_timeout,
			&timeout);
}