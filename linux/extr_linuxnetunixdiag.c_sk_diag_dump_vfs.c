#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv ;
struct unix_diag_vfs {int /*<<< orphan*/  udiag_vfs_dev; int /*<<< orphan*/  udiag_vfs_ino; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dentry {TYPE_2__* d_sb; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct TYPE_7__ {TYPE_1__ path; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNIX_DIAG_VFS ; 
 TYPE_4__* d_backing_inode (struct dentry*) ; 
 int nla_put (struct sk_buff*,int /*<<< orphan*/ ,int,struct unix_diag_vfs*) ; 
 TYPE_3__* unix_sk (struct sock*) ; 

__attribute__((used)) static int sk_diag_dump_vfs(struct sock *sk, struct sk_buff *nlskb)
{
	struct dentry *dentry = unix_sk(sk)->path.dentry;

	if (dentry) {
		struct unix_diag_vfs uv = {
			.udiag_vfs_ino = d_backing_inode(dentry)->i_ino,
			.udiag_vfs_dev = dentry->d_sb->s_dev,
		};

		return nla_put(nlskb, UNIX_DIAG_VFS, sizeof(uv), &uv);
	}

	return 0;
}