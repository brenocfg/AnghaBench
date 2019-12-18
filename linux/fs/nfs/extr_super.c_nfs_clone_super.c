#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int s_time_gran; int /*<<< orphan*/  s_time_max; scalar_t__ s_time_min; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_export_op; int /*<<< orphan*/  s_op; int /*<<< orphan*/  s_xattr; int /*<<< orphan*/  s_maxbytes; int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_blocksize_bits; } ;
struct nfs_server {TYPE_3__* nfs_client; } ;
struct nfs_mount_info {TYPE_1__* cloned; } ;
struct TYPE_6__ {TYPE_2__* rpc_ops; } ;
struct TYPE_5__ {int version; } ;
struct TYPE_4__ {struct super_block* sb; } ;

/* Variables and functions */
 struct nfs_server* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  S64_MAX ; 
 scalar_t__ S64_MIN ; 
 int /*<<< orphan*/  SB_POSIXACL ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  nfs_initialise_sb (struct super_block*) ; 

__attribute__((used)) static void nfs_clone_super(struct super_block *sb,
			    struct nfs_mount_info *mount_info)
{
	const struct super_block *old_sb = mount_info->cloned->sb;
	struct nfs_server *server = NFS_SB(sb);

	sb->s_blocksize_bits = old_sb->s_blocksize_bits;
	sb->s_blocksize = old_sb->s_blocksize;
	sb->s_maxbytes = old_sb->s_maxbytes;
	sb->s_xattr = old_sb->s_xattr;
	sb->s_op = old_sb->s_op;
	sb->s_export_op = old_sb->s_export_op;

	if (server->nfs_client->rpc_ops->version != 2) {
		/* The VFS shouldn't apply the umask to mode bits. We will do
		 * so ourselves when necessary.
		 */
		sb->s_flags |= SB_POSIXACL;
		sb->s_time_gran = 1;
	} else
		sb->s_time_gran = 1000;

	if (server->nfs_client->rpc_ops->version != 4) {
		sb->s_time_min = 0;
		sb->s_time_max = U32_MAX;
	} else {
		sb->s_time_min = S64_MIN;
		sb->s_time_max = S64_MAX;
	}

 	nfs_initialise_sb(sb);
}