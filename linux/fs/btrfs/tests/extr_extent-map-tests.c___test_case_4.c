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
struct extent_map {scalar_t__ start; int len; int block_len; scalar_t__ block_start; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ SZ_16K ; 
 int SZ_1K ; 
 void* SZ_32K ; 
 scalar_t__ SZ_4K ; 
 void* SZ_8K ; 
 int /*<<< orphan*/  TEST_ALLOC_EXTENT_MAP ; 
 int add_extent_mapping (struct extent_map_tree*,struct extent_map*,int /*<<< orphan*/ ) ; 
 struct extent_map* alloc_extent_map () ; 
 int btrfs_add_extent_mapping (struct btrfs_fs_info*,struct extent_map_tree*,struct extent_map**,scalar_t__,scalar_t__) ; 
 scalar_t__ extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map_tree (struct extent_map_tree*) ; 
 int /*<<< orphan*/  test_err (char*,...) ; 
 int /*<<< orphan*/  test_std_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __test_case_4(struct btrfs_fs_info *fs_info,
		struct extent_map_tree *em_tree, u64 start)
{
	struct extent_map *em;
	u64 len = SZ_4K;
	int ret;

	em = alloc_extent_map();
	if (!em) {
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		return -ENOMEM;
	}

	/* Add [0K, 8K) */
	em->start = 0;
	em->len = SZ_8K;
	em->block_start = 0;
	em->block_len = SZ_8K;
	write_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	write_unlock(&em_tree->lock);
	if (ret < 0) {
		test_err("cannot add extent range [0, 8K)");
		goto out;
	}
	free_extent_map(em);

	em = alloc_extent_map();
	if (!em) {
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		goto out;
	}

	/* Add [8K, 32K) */
	em->start = SZ_8K;
	em->len = 24 * SZ_1K;
	em->block_start = SZ_16K; /* avoid merging */
	em->block_len = 24 * SZ_1K;
	write_lock(&em_tree->lock);
	ret = add_extent_mapping(em_tree, em, 0);
	write_unlock(&em_tree->lock);
	if (ret < 0) {
		test_err("cannot add extent range [8K, 32K)");
		goto out;
	}
	free_extent_map(em);

	em = alloc_extent_map();
	if (!em) {
		test_std_err(TEST_ALLOC_EXTENT_MAP);
		ret = -ENOMEM;
		goto out;
	}
	/* Add [0K, 32K) */
	em->start = 0;
	em->len = SZ_32K;
	em->block_start = 0;
	em->block_len = SZ_32K;
	write_lock(&em_tree->lock);
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, start, len);
	write_unlock(&em_tree->lock);
	if (ret) {
		test_err("case4 [0x%llx 0x%llx): ret %d",
			 start, len, ret);
		goto out;
	}
	if (em && (start < em->start || start + len > extent_map_end(em))) {
		test_err(
"case4 [0x%llx 0x%llx): ret %d, added wrong em (start 0x%llx len 0x%llx block_start 0x%llx block_len 0x%llx)",
			 start, len, ret, em->start, em->len, em->block_start,
			 em->block_len);
		ret = -EINVAL;
	}
	free_extent_map(em);
out:
	free_extent_map_tree(em_tree);

	return ret;
}