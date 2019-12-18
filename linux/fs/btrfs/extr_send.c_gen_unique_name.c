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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  tmp ;
struct send_ctx {int /*<<< orphan*/  parent_root; int /*<<< orphan*/  send_root; } ;
struct fs_path {int dummy; } ;
struct btrfs_path {int dummy; } ;
struct btrfs_dir_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BTRFS_FIRST_FREE_OBJECTID ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct btrfs_dir_item*) ; 
 int PTR_ERR (struct btrfs_dir_item*) ; 
 struct btrfs_path* alloc_path_for_send () ; 
 int /*<<< orphan*/  btrfs_free_path (struct btrfs_path*) ; 
 struct btrfs_dir_item* btrfs_lookup_dir_item (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct btrfs_path*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_release_path (struct btrfs_path*) ; 
 int fs_path_add (struct fs_path*,char*,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int gen_unique_name(struct send_ctx *sctx,
			   u64 ino, u64 gen,
			   struct fs_path *dest)
{
	int ret = 0;
	struct btrfs_path *path;
	struct btrfs_dir_item *di;
	char tmp[64];
	int len;
	u64 idx = 0;

	path = alloc_path_for_send();
	if (!path)
		return -ENOMEM;

	while (1) {
		len = snprintf(tmp, sizeof(tmp), "o%llu-%llu-%llu",
				ino, gen, idx);
		ASSERT(len < sizeof(tmp));

		di = btrfs_lookup_dir_item(NULL, sctx->send_root,
				path, BTRFS_FIRST_FREE_OBJECTID,
				tmp, strlen(tmp), 0);
		btrfs_release_path(path);
		if (IS_ERR(di)) {
			ret = PTR_ERR(di);
			goto out;
		}
		if (di) {
			/* not unique, try again */
			idx++;
			continue;
		}

		if (!sctx->parent_root) {
			/* unique */
			ret = 0;
			break;
		}

		di = btrfs_lookup_dir_item(NULL, sctx->parent_root,
				path, BTRFS_FIRST_FREE_OBJECTID,
				tmp, strlen(tmp), 0);
		btrfs_release_path(path);
		if (IS_ERR(di)) {
			ret = PTR_ERR(di);
			goto out;
		}
		if (di) {
			/* not unique, try again */
			idx++;
			continue;
		}
		/* unique */
		break;
	}

	ret = fs_path_add(dest, tmp, strlen(tmp));

out:
	btrfs_free_path(path);
	return ret;
}