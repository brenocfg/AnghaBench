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
struct rpc_pipe_dir_object_ops {int dummy; } ;
struct rpc_pipe_dir_object {void* pdo_data; struct rpc_pipe_dir_object_ops const* pdo_ops; int /*<<< orphan*/  pdo_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void rpc_init_pipe_dir_object(struct rpc_pipe_dir_object *pdo,
		const struct rpc_pipe_dir_object_ops *pdo_ops,
		void *pdo_data)
{
	INIT_LIST_HEAD(&pdo->pdo_head);
	pdo->pdo_ops = pdo_ops;
	pdo->pdo_data = pdo_data;
}