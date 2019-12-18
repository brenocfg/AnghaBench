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
struct send_ctx {int dummy; } ;
struct fs_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_SEND_A_PATH ; 
 int /*<<< orphan*/  BTRFS_SEND_A_XATTR_NAME ; 
 int /*<<< orphan*/  BTRFS_SEND_C_REMOVE_XATTR ; 
 int /*<<< orphan*/  TLV_PUT_PATH (struct send_ctx*,int /*<<< orphan*/ ,struct fs_path*) ; 
 int /*<<< orphan*/  TLV_PUT_STRING (struct send_ctx*,int /*<<< orphan*/ ,char const*,int) ; 
 int begin_cmd (struct send_ctx*,int /*<<< orphan*/ ) ; 
 int send_cmd (struct send_ctx*) ; 

__attribute__((used)) static int send_remove_xattr(struct send_ctx *sctx,
			  struct fs_path *path,
			  const char *name, int name_len)
{
	int ret = 0;

	ret = begin_cmd(sctx, BTRFS_SEND_C_REMOVE_XATTR);
	if (ret < 0)
		goto out;

	TLV_PUT_PATH(sctx, BTRFS_SEND_A_PATH, path);
	TLV_PUT_STRING(sctx, BTRFS_SEND_A_XATTR_NAME, name, name_len);

	ret = send_cmd(sctx);

tlv_put_failure:
out:
	return ret;
}