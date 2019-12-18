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
typedef  int /*<<< orphan*/  u8 ;
struct send_ctx {int /*<<< orphan*/  cur_inode_gen; int /*<<< orphan*/  cur_ino; } ;
struct posix_acl_xattr_header {int /*<<< orphan*/  a_version; } ;
struct fs_path {int dummy; } ;
struct btrfs_key {int dummy; } ;
typedef  int /*<<< orphan*/  dummy_acl ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  POSIX_ACL_XATTR_VERSION ; 
 int /*<<< orphan*/  XATTR_NAME_POSIX_ACL_ACCESS ; 
 int /*<<< orphan*/  XATTR_NAME_POSIX_ACL_DEFAULT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int get_cur_path (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int send_set_xattr (struct send_ctx*,struct fs_path*,char const*,int,char const*,int) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __process_new_xattr(int num, struct btrfs_key *di_key,
			       const char *name, int name_len,
			       const char *data, int data_len,
			       u8 type, void *ctx)
{
	int ret;
	struct send_ctx *sctx = ctx;
	struct fs_path *p;
	struct posix_acl_xattr_header dummy_acl;

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

	/*
	 * This hack is needed because empty acls are stored as zero byte
	 * data in xattrs. Problem with that is, that receiving these zero byte
	 * acls will fail later. To fix this, we send a dummy acl list that
	 * only contains the version number and no entries.
	 */
	if (!strncmp(name, XATTR_NAME_POSIX_ACL_ACCESS, name_len) ||
	    !strncmp(name, XATTR_NAME_POSIX_ACL_DEFAULT, name_len)) {
		if (data_len == 0) {
			dummy_acl.a_version =
					cpu_to_le32(POSIX_ACL_XATTR_VERSION);
			data = (char *)&dummy_acl;
			data_len = sizeof(dummy_acl);
		}
	}

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	if (ret < 0)
		goto out;

	ret = send_set_xattr(sctx, p, name, name_len, data, data_len);

out:
	fs_path_free(p);
	return ret;
}