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
struct send_ctx {TYPE_1__* send_root; } ;
struct fs_path {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_A_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_A_SIZE ; 
 int /*<<< orphan*/  BTRFS_SEND_C_TRUNCATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TLV_PUT_PATH (struct send_ctx*,int /*<<< orphan*/ ,struct fs_path*) ; 
 int /*<<< orphan*/  TLV_PUT_U64 (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int begin_cmd (struct send_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_debug (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int get_cur_path (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int send_cmd (struct send_ctx*) ; 

__attribute__((used)) static int send_truncate(struct send_ctx *sctx, u64 ino, u64 gen, u64 size)
{
	struct btrfs_fs_info *fs_info = sctx->send_root->fs_info;
	int ret = 0;
	struct fs_path *p;

	btrfs_debug(fs_info, "send_truncate %llu size=%llu", ino, size);

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_TRUNCATE);
	if (ret < 0)
		goto out;

	ret = get_cur_path(sctx, ino, gen, p);
	if (ret < 0)
		goto out;
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_SIZE, size);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_free(p);
	return ret;
}