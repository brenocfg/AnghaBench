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
 int ENOMEM ; 
 struct nilfs_btree_path* nilfs_btree_alloc_path () ; 
 int nilfs_btree_do_lookup (struct nilfs_bmap const*,struct nilfs_btree_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_free_path (struct nilfs_btree_path*) ; 

__attribute__((used)) static int nilfs_btree_lookup(const struct nilfs_bmap *btree,
			      __u64 key, int level, __u64 *ptrp)
{
	struct nilfs_btree_path *path;
	int ret;

	path = nilfs_btree_alloc_path();
	if (path == NULL)
		return -ENOMEM;

	ret = nilfs_btree_do_lookup(btree, path, key, ptrp, level, 0);

	nilfs_btree_free_path(path);

	return ret;
}