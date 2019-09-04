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
struct extent_map_tree {int dummy; } ;
struct extent_map {scalar_t__ start; int len; int block_len; scalar_t__ block_start; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ SZ_16K ; 
 void* SZ_32K ; 
 scalar_t__ SZ_4K ; 
 void* SZ_8K ; 
 int add_extent_mapping (struct extent_map_tree*,struct extent_map*,int /*<<< orphan*/ ) ; 
 struct extent_map* alloc_extent_map () ; 
 int btrfs_add_extent_mapping (struct btrfs_fs_info*,struct extent_map_tree*,struct extent_map**,scalar_t__,scalar_t__) ; 
 scalar_t__ extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map_tree (struct extent_map_tree*) ; 
 int /*<<< orphan*/  test_err (char*,scalar_t__,scalar_t__,int,...) ; 

__attribute__((used)) static void __test_case_4(struct btrfs_fs_info *fs_info,
		struct extent_map_tree *em_tree, u64 start)
{
	struct extent_map *em;
	u64 len = SZ_4K;
	int ret;

	em = alloc_extent_map();
	if (!em)
		/* Skip this test on error. */
		return;

	/* Add [0K, 8K) */
	em->start = 0;
	em->len = SZ_8K;
	em->block_start = 0;
	em->block_len = SZ_8K;
	ret = add_extent_mapping(em_tree, em, 0);
	ASSERT(ret == 0);
	free_extent_map(em);

	em = alloc_extent_map();
	if (!em)
		goto out;

	/* Add [8K, 24K) */
	em->start = SZ_8K;
	em->len = 24 * 1024ULL;
	em->block_start = SZ_16K; /* avoid merging */
	em->block_len = 24 * 1024ULL;
	ret = add_extent_mapping(em_tree, em, 0);
	ASSERT(ret == 0);
	free_extent_map(em);

	em = alloc_extent_map();
	if (!em)
		goto out;
	/* Add [0K, 32K) */
	em->start = 0;
	em->len = SZ_32K;
	em->block_start = 0;
	em->block_len = SZ_32K;
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, start, len);
	if (ret)
		test_err("case4 [0x%llx 0x%llx): ret %d",
			 start, len, ret);
	if (em &&
	    (start < em->start || start + len > extent_map_end(em)))
		test_err(
"case4 [0x%llx 0x%llx): ret %d, added wrong em (start 0x%llx len 0x%llx block_start 0x%llx block_len 0x%llx)",
			 start, len, ret, em->start, em->len, em->block_start,
			 em->block_len);
	free_extent_map(em);
out:
	/* free memory */
	free_extent_map_tree(em_tree);
}