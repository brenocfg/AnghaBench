#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct send_ctx {TYPE_3__* send_root; int /*<<< orphan*/  cur_inode_gen; int /*<<< orphan*/  cur_ino; } ;
struct fs_path {int dummy; } ;
struct clone_root {int /*<<< orphan*/  offset; TYPE_3__* root; int /*<<< orphan*/  ino; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctransid; int /*<<< orphan*/  uuid; int /*<<< orphan*/  received_uuid; } ;
struct TYPE_5__ {int /*<<< orphan*/  objectid; } ;
struct TYPE_7__ {TYPE_2__ root_item; TYPE_1__ root_key; int /*<<< orphan*/  fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_A_CLONE_CTRANSID ; 
 int /*<<< orphan*/  BTRFS_SEND_A_CLONE_LEN ; 
 int /*<<< orphan*/  BTRFS_SEND_A_CLONE_OFFSET ; 
 int /*<<< orphan*/  BTRFS_SEND_A_CLONE_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_A_CLONE_UUID ; 
 int /*<<< orphan*/  BTRFS_SEND_A_FILE_OFFSET ; 
 int /*<<< orphan*/  BTRFS_SEND_A_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_C_CLONE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TLV_PUT_PATH (struct send_ctx*,int /*<<< orphan*/ ,struct fs_path*) ; 
 int /*<<< orphan*/  TLV_PUT_U64 (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TLV_PUT_UUID (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int begin_cmd (struct send_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_is_empty_uuid (int /*<<< orphan*/ ) ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int get_cur_path (struct send_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fs_path*) ; 
 int get_inode_info (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_inode_path (TYPE_3__*,int /*<<< orphan*/ ,struct fs_path*) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int send_cmd (struct send_ctx*) ; 

__attribute__((used)) static int send_clone(struct send_ctx *sctx,
		      u64 offset, u32 len,
		      struct clone_root *clone_root)
{
	int ret = 0;
	struct fs_path *p;
	u64 gen;

	btrfs_debug(sctx->send_root->fs_info,
		    "send_clone offset=%llu, len=%d, clone_root=%llu, clone_inode=%llu, clone_offset=%llu",
		    offset, len, clone_root->root->root_key.objectid,
		    clone_root->ino, clone_root->offset);

	p = fs_path_alloc();
	if (!p)
		return -ENOMEM;

	ret = begin_cmd(sctx, BTRFS_SEND_C_CLONE);
	if (ret < 0)
		goto out;

	ret = get_cur_path(sctx, sctx->cur_ino, sctx->cur_inode_gen, p);
	if (ret < 0)
		goto out;

	TLV_PUT_U64(sctx, BTRFS_SEND_A_FILE_OFFSET, offset);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_CLONE_LEN, len);
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, p);

	if (clone_root->root == sctx->send_root) {
		ret = get_inode_info(sctx->send_root, clone_root->ino, NULL,
				&gen, NULL, NULL, NULL, NULL);
		if (ret < 0)
			goto out;
		ret = get_cur_path(sctx, clone_root->ino, gen, p);
	} else {
		ret = get_inode_path(clone_root->root, clone_root->ino, p);
	}
	if (ret < 0)
		goto out;

	/*
	 * If the parent we're using has a received_uuid set then use that as
	 * our clone source as that is what we will look for when doing a
	 * receive.
	 *
	 * This covers the case that we create a snapshot off of a received
	 * subvolume and then use that as the parent and try to receive on a
	 * different host.
	 */
	if (!btrfs_is_empty_uuid(clone_root->root->root_item.received_uuid))
		TLV_PUT_UUID(sctx, BTRFS_SEND_A_CLONE_UUID,
			     clone_root->root->root_item.received_uuid);
	else
		TLV_PUT_UUID(sctx, BTRFS_SEND_A_CLONE_UUID,
			     clone_root->root->root_item.uuid);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_CLONE_CTRANSID,
		    le64_to_cpu(clone_root->root->root_item.ctransid));
	TLV_PUT_PATH(sctx, BTRFS_SEND_A_CLONE_PATH, p);
	TLV_PUT_U64(sctx, BTRFS_SEND_A_CLONE_OFFSET,
			clone_root->offset);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	fs_path_free(p);
	return ret;
}