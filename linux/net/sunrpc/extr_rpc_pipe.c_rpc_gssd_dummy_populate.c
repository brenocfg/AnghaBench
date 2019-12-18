#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpc_pipe {int dummy; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 struct qstr QSTR_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t RPCAUTH_gssd ; 
 int /*<<< orphan*/  __rpc_depopulate (struct dentry*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 struct dentry* d_hash_and_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 TYPE_4__* files ; 
 TYPE_1__* gssd_dummy_clnt_dir ; 
 TYPE_1__* gssd_dummy_info_file ; 
 struct dentry* rpc_mkpipe_dentry (struct dentry*,char*,int /*<<< orphan*/ *,struct rpc_pipe*) ; 
 int rpc_populate (struct dentry*,TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *
rpc_gssd_dummy_populate(struct dentry *root, struct rpc_pipe *pipe_data)
{
	int ret = 0;
	struct dentry *gssd_dentry;
	struct dentry *clnt_dentry = NULL;
	struct dentry *pipe_dentry = NULL;
	struct qstr q = QSTR_INIT(files[RPCAUTH_gssd].name,
				  strlen(files[RPCAUTH_gssd].name));

	/* We should never get this far if "gssd" doesn't exist */
	gssd_dentry = d_hash_and_lookup(root, &q);
	if (!gssd_dentry)
		return ERR_PTR(-ENOENT);

	ret = rpc_populate(gssd_dentry, gssd_dummy_clnt_dir, 0, 1, NULL);
	if (ret) {
		pipe_dentry = ERR_PTR(ret);
		goto out;
	}

	q.name = gssd_dummy_clnt_dir[0].name;
	q.len = strlen(gssd_dummy_clnt_dir[0].name);
	clnt_dentry = d_hash_and_lookup(gssd_dentry, &q);
	if (!clnt_dentry) {
		pipe_dentry = ERR_PTR(-ENOENT);
		goto out;
	}

	ret = rpc_populate(clnt_dentry, gssd_dummy_info_file, 0, 1, NULL);
	if (ret) {
		__rpc_depopulate(gssd_dentry, gssd_dummy_clnt_dir, 0, 1);
		pipe_dentry = ERR_PTR(ret);
		goto out;
	}

	pipe_dentry = rpc_mkpipe_dentry(clnt_dentry, "gssd", NULL, pipe_data);
	if (IS_ERR(pipe_dentry)) {
		__rpc_depopulate(clnt_dentry, gssd_dummy_info_file, 0, 1);
		__rpc_depopulate(gssd_dentry, gssd_dummy_clnt_dir, 0, 1);
	}
out:
	dput(clnt_dentry);
	dput(gssd_dentry);
	return pipe_dentry;
}