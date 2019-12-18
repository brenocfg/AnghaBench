#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_dev; int /*<<< orphan*/  s_d_op; struct nfs_server* s_fs_info; int /*<<< orphan*/  s_flags; } ;
struct nfs_server {int /*<<< orphan*/  s_dev; TYPE_1__* nfs_client; } ;
struct nfs_sb_mountdata {int /*<<< orphan*/  mntflags; struct nfs_server* server; } ;
struct TYPE_4__ {int /*<<< orphan*/  dentry_ops; } ;
struct TYPE_3__ {TYPE_2__* rpc_ops; } ;

/* Variables and functions */
 int set_anon_super (struct super_block*,struct nfs_server*) ; 

__attribute__((used)) static int nfs_set_super(struct super_block *s, void *data)
{
	struct nfs_sb_mountdata *sb_mntdata = data;
	struct nfs_server *server = sb_mntdata->server;
	int ret;

	s->s_flags = sb_mntdata->mntflags;
	s->s_fs_info = server;
	s->s_d_op = server->nfs_client->rpc_ops->dentry_ops;
	ret = set_anon_super(s, server);
	if (ret == 0)
		server->s_dev = s->s_dev;
	return ret;
}