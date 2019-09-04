#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct send_ctx {int cur_ino; int cur_inode_gen; int cur_inode_mode; int cur_inode_rdev; TYPE_1__* send_root; } ;
struct fs_path {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_3__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_A_INO ; 
 int /*<<< orphan*/  BTRFS_SEND_A_MODE ; 
 int /*<<< orphan*/  BTRFS_SEND_A_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_A_PATH_LINK ; 
 int /*<<< orphan*/  BTRFS_SEND_A_RDEV ; 
 int BTRFS_SEND_C_MKDIR ; 
 int BTRFS_SEND_C_MKFIFO ; 
 int BTRFS_SEND_C_MKFILE ; 
 int BTRFS_SEND_C_MKNOD ; 
 int BTRFS_SEND_C_MKSOCK ; 
 int BTRFS_SEND_C_SYMLINK ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int S_IFMT ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int /*<<< orphan*/  TLV_PUT_PATH (struct send_ctx*,int /*<<< orphan*/ ,struct fs_path*) ; 
 int /*<<< orphan*/  TLV_PUT_U64 (struct send_ctx*,int /*<<< orphan*/ ,int) ; 
 int begin_cmd (struct send_ctx*,int) ; 
 int /*<<< orphan*/  btrfs_debug (struct btrfs_fs_info*,char*,int) ; 
 int /*<<< orphan*/  btrfs_warn (struct btrfs_fs_info*,char*,int) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int /*<<< orphan*/  fs_path_reset (struct fs_path*) ; 
 int gen_unique_name (struct send_ctx*,int,int,struct fs_path*) ; 
 int get_inode_info (TYPE_1__*,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int new_encode_dev (int) ; 
 int read_symlink (TYPE_1__*,int,struct fs_path*) ; 
 int send_cmd (struct send_ctx*) ; 

__attribute__((used)) static int send_create_inode(struct send_ctx *sctx, u64 ino)
{
	struct btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	int ret = 0;
	struct fs_path *p;
	int cmd;
	u64 gen;
	u64 mode;
	u64 rdev;

	btrfs_debug(fs_info, "send_create_inode %llu", ino);

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

	if (ino != sctx->cur_ino) {
		ret = get_inode_info(sctx->send_root, ino, NULL, &gen, &mode,
				     NULL, NULL, &rdev);
		if (ret < 0)
			goto out;
	} else {
		gen = sctx->cur_inode_gen;
		mode = sctx->cur_inode_mode;
		rdev = sctx->cur_inode_rdev;
	}

	if (S_ISREG(mode)) {
		cmd = BTRFS_SEND_C_MKFILE;
	} else if (S_ISDIR(mode)) {
		cmd = BTRFS_SEND_C_MKDIR;
	} else if (S_ISLNK(mode)) {
		cmd = BTRFS_SEND_C_SYMLINK;
	} else if (S_ISCHR(mode) || S_ISBLK(mode)) {
		cmd = BTRFS_SEND_C_MKNOD;
	} else if (S_ISFIFO(mode)) {
		cmd = BTRFS_SEND_C_MKFIFO;
	} else if (S_ISSOCK(mode)) {
		cmd = BTRFS_SEND_C_MKSOCK;
	} else {
		btrfs_warn(sctx->send_root->fs_info, "unexpected inode type %o",
				(int)(mode & S_IFMT));
		ret = -EOPNOTSUPP;
		goto out;
	}

	ret = begin_cmd(sctx, cmd);
	if (ret < 0)
		goto out;

	ret = gen_unique_name(sctx, ino, gen, p);
	if (ret < 0)
		goto out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_INO, ino);

	if (S_ISLNK(mode)) {
		fs_path_reset(p);
		ret = read_symlink(sctx->send_root, ino, p);
		if (ret < 0)
			goto out;
		TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH_LINK, p);
	} else if (S_ISCHR(mode) || S_ISBLK(mode) ||
		   S_ISFIFO(mode) || S_ISSOCK(mode)) {
		TLV_PUT_U64(sctx, BTRFS_SEND_A_RDEV, new_encode_dev(rdev));
		TLV_PUT_U64(sctx, BTRFS_SEND_A_MODE, mode);
	}

	ret = send_cmd(sctx);
	if (ret < 0)
		goto out;


tlv_put_failure:
out:
	fs_path_free(p);
	return ret;
}