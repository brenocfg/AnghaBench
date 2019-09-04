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
struct rpc_pipe_dir_object {struct idmap* pdo_data; } ;
struct rpc_pipe {int /*<<< orphan*/ * dentry; } ;
struct idmap {struct rpc_pipe* idmap_pipe; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_unlink (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_idmap_pipe_destroy(struct dentry *dir,
		struct rpc_pipe_dir_object *pdo)
{
	struct idmap *idmap = pdo->pdo_data;
	struct rpc_pipe *pipe = idmap->idmap_pipe;

	if (pipe->dentry) {
		rpc_unlink(pipe->dentry);
		pipe->dentry = NULL;
	}
}