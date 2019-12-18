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
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {scalar_t__ start; scalar_t__ block_start; scalar_t__ block_len; void* len; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ EXTENT_MAP_INLINE ; 
 scalar_t__ SZ_1K ; 
 void* SZ_4K ; 
 int /*<<< orphan*/  TEST_ALLOC_EXTENT_MAP ; 
 int add_extent_mapping (struct extent_map_tree*,struct extent_map*,int /*<<< orphan*/ ) ; 
 struct extent_map* alloc_extent_map () ; 
 int btrfs_add_extent_mapping (struct btrfs_fs_info*,struct extent_map_tree*,struct extent_map**,scalar_t__,void*) ; 
 scalar_t__ extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map_tree (struct extent_map_tree*) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_case_2(struct btrfs_fs_info *fs_info,
		struct extent_map_tree *em_tree)
{
	struct extent_map *em;
	int ret;

	em = alloc_extent_map();
	if (!em) {
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		return -ENOMEM;
	}

	/* Add [0, 1K) */
	em->start = 0;
	em->len = SZ_1K;
	em->block_start = EXTENT_MAP_INLINE;
	em->block_len = (u64)-1;
	write_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	write_unlock(&em_tree->lock);
	if (ret < 0) {
		test_err("cannot add extent range [0, 1K)");
		goto out;
	}
	free_extent_map(em);

	/* Add [4K, 8K) following [0, 1K)  */
	em = alloc_extent_map();
	if (!em) {
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		goto out;
	}

	em->start = SZ_4K;
	em->len = SZ_4K;
	em->block_start = SZ_4K;
	em->block_len = SZ_4K;
	write_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	write_unlock(&em_tree->lock);
	if (ret < 0) {
		test_err("cannot add extent range [4K, 8K)");
		goto out;
	}
	free_extent_map(em);

	em = alloc_extent_map();
	if (!em) {
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		goto out;
	}

	/* Add [0, 1K) */
	em->start = 0;
	em->len = SZ_1K;
	em->block_start = EXTENT_MAP_INLINE;
	em->block_len = (u64)-1;
	write_lock(&em_tree->lock);
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, em->start, em->len);
	write_unlock(&em_tree->lock);
	if (ret) {
		test_err("case2 [0 1K]: ret %d", ret);
		goto out;
	}
	if (em &&
	    (em->start != 0 || extent_map_end(em) != SZ_1K ||
	     em->block_start != EXTENT_MAP_INLINE || em->block_len != (u64)-1)) {
		test_err(
"case2 [0 1K]: ret %d return a wrong em (start %llu len %llu block_start %llu block_len %llu",
			 ret, em->start, em->len, em->block_start,
			 em->block_len);
		ret = -EINVAL;
	}
	free_extent_map(em);
out:
	free_extent_map_tree(em_tree);

	return ret;
}