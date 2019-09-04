#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct send_ctx {int /*<<< orphan*/  read_buf; int /*<<< orphan*/  cur_inode_gen; int /*<<< orphan*/  cur_ino; TYPE_1__* send_root; } ;
struct fs_path {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_A_DATA ; 
 int /*<<< orphan*/  BTRFS_SEND_A_FILE_OFFSET ; 
 int /*<<< orphan*/  BTRFS_SEND_A_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_C_WRITE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TLV_PUT (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TLV_PUT_PATH (struct send_ctx*,int /*<<< orphan*/ ,struct fs_path*) ; 
 int /*<<< orphan*/  TLV_PUT_U64 (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int begin_cmd (struct send_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_debug (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fill_read_buf (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int get_cur_path (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int send_cmd (struct send_ctx*) ; 

__attribute__((used)) static int send_write(struct send_ctx *sctx, u64 offset, u32 len)
{
	struct btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	int ret = 0;
	struct fs_path *p;
	ssize_t num_read = 0;

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

	btrfs_debug(fs_info, "send_write offset=%llu, len=%d", offset, len);

	num_read = fill_read_buf(sctx, offset, len);
	if (num_read <= 0) {
		if (num_read < 0)
			ret = num_read;
		goto out;
	}

	ret = begin_cmd(sctx, BTRFS_SEND_C_WRITE);
	if (ret < 0)
		goto out;

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	if (ret < 0)
		goto out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_FILE_OFFSET, offset);
	TLV_PUT(sctx, BTRFS_SEND_A_DATA, sctx->read_buf, num_read);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_free(p);
	if (ret < 0)
		return ret;
	return num_read;
}