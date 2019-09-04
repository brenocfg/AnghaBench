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
struct rpc_pipe {struct dentry* dentry; } ;
struct idmap {struct rpc_pipe* idmap_pipe; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 struct dentry* rpc_mkpipe_dentry (struct dentry*,char*,struct idmap*,struct rpc_pipe*) ; 

__attribute__((used)) static int nfs_idmap_pipe_create(struct dentry *dir,
		struct rpc_pipe_dir_object *pdo)
{
	struct idmap *idmap = pdo->pdo_data;
	struct rpc_pipe *pipe = idmap->idmap_pipe;
	struct dentry *dentry;

	dentry = rpc_mkpipe_dentry(dir, "idmap", idmap, pipe);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);
	pipe->dentry = dentry;
	return 0;
}