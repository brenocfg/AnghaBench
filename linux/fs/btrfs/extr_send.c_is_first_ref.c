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
struct fs_path {int /*<<< orphan*/  start; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct fs_path* fs_path_alloc () ; 
 int /*<<< orphan*/  fs_path_free (struct fs_path*) ; 
 int fs_path_len (struct fs_path*) ; 
 int get_first_ref (struct btrfs_root*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *,struct fs_path*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static int is_first_ref(struct btrfs_root *root,
			u64 ino, u64 dir,
			const char *name, int name_len)
{
	int ret;
	struct fs_path *tmp_name;
	u64 tmp_dir;

	tmp_name = fs_path_alloc();
	if (!tmp_name)
		return -ENOMEM;

	ret = get_first_ref(root, ino, &tmp_dir, NULL, tmp_name);
	if (ret < 0)
		goto out;

	if (dir != tmp_dir || name_len != fs_path_len(tmp_name)) {
		ret = 0;
		goto out;
	}

	ret = !memcmp(tmp_name->start, name, name_len);

out:
	fs_path_free(tmp_name);
	return ret;
}