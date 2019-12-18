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
struct nilfs_btree_path {int dummy; } ;
struct nilfs_bmap {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int NILFS_BTREE_LEVEL_NODE_MIN ; 
 struct nilfs_btree_path* nilfs_btree_alloc_path () ; 
 int nilfs_btree_do_lookup (struct nilfs_bmap const*,struct nilfs_btree_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_free_path (struct nilfs_btree_path*) ; 
 int nilfs_btree_get_next_key (struct nilfs_bmap const*,struct nilfs_btree_path*,int const,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_btree_seek_key(const struct nilfs_bmap *btree, __u64 start,
				__u64 *keyp)
{
	struct nilfs_btree_path *path;
	const int minlevel = NILFS_BTREE_LEVEL_NODE_MIN;
	int ret;

	path = nilfs_btree_alloc_path();
	if (!path)
		return -ENOMEM;

	ret = nilfs_btree_do_lookup(btree, path, start, NULL, minlevel, 0);
	if (!ret)
		*keyp = start;
	else if (ret == -ENOENT)
		ret = nilfs_btree_get_next_key(btree, path, minlevel, keyp);

	nilfs_btree_free_path(path);
	return ret;
}