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
struct rpc_task {int dummy; } ;
struct nlmclnt_operations {int (* nlmclnt_unlock_prepare ) (struct rpc_task*,int /*<<< orphan*/ ) ;} ;
struct nlm_rqst {int /*<<< orphan*/  a_callback_data; TYPE_1__* a_host; } ;
struct TYPE_2__ {struct nlmclnt_operations* h_nlmclnt_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_call_start (struct rpc_task*) ; 
 int stub1 (struct rpc_task*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nlmclnt_unlock_prepare(struct rpc_task *task, void *data)
{
	struct nlm_rqst	*req = data;
	const struct nlmclnt_operations *nlmclnt_ops = req->a_host->h_nlmclnt_ops;
	bool defer_call = false;

	if (nlmclnt_ops && nlmclnt_ops->nlmclnt_unlock_prepare)
		defer_call = nlmclnt_ops->nlmclnt_unlock_prepare(task, req->a_callback_data);

	if (!defer_call)
		rpc_call_start(task);
}