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
struct rpc_pipe_dir_object {struct gss_pipe* pdo_data; } ;
struct rpc_pipe {int /*<<< orphan*/ * dentry; } ;
struct gss_pipe {struct rpc_pipe* pipe; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gss_pipe_dentry_destroy(struct dentry *dir,
		struct rpc_pipe_dir_object *pdo)
{
	struct gss_pipe *gss_pipe = pdo->pdo_data;
	struct rpc_pipe *pipe = gss_pipe->pipe;

	if (pipe->dentry != NULL) {
		rpc_unlink(pipe->dentry);
		pipe->dentry = NULL;
	}
}