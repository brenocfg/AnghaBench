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
struct send_ctx {int /*<<< orphan*/  cmp_key; int /*<<< orphan*/  left_path; int /*<<< orphan*/  send_root; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int __process_deleted_xattr (int,struct btrfs_key*,char const*,int,char const*,int,int /*<<< orphan*/ ,void*) ; 
 int find_xattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __process_changed_deleted_xattr(int num, struct btrfs_key *di_key,
					   const char *name, int name_len,
					   const char *data, int data_len,
					   u8 type, void *ctx)
{
	int ret;
	struct send_ctx *sctx = ctx;

	ret = find_xattr(sctx->send_root, sctx->left_path, sctx->cmp_key,
			 name, name_len, NULL, NULL);
	if (ret == -ENOENT)
		ret = __process_deleted_xattr(num, di_key, name, name_len, data,
				data_len, type, ctx);
	else if (ret >= 0)
		ret = 0;

	return ret;
}