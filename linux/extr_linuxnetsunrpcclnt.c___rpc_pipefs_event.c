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
struct super_block {int dummy; } ;
struct rpc_clnt {struct rpc_clnt* cl_parent; } ;

/* Variables and functions */
 int __rpc_clnt_handle_event (struct rpc_clnt*,unsigned long,struct super_block*) ; 
 int /*<<< orphan*/  rpc_clnt_skip_event (struct rpc_clnt*,unsigned long) ; 

__attribute__((used)) static int __rpc_pipefs_event(struct rpc_clnt *clnt, unsigned long event,
				struct super_block *sb)
{
	int error = 0;

	for (;; clnt = clnt->cl_parent) {
		if (!rpc_clnt_skip_event(clnt, event))
			error = __rpc_clnt_handle_event(clnt, event, sb);
		if (error || clnt == clnt->cl_parent)
			break;
	}
	return error;
}