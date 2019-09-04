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
struct extent_map {scalar_t__ start; scalar_t__ block_start; scalar_t__ block_len; void* len; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ EXTENT_MAP_INLINE ; 
 scalar_t__ SZ_1K ; 
 void* SZ_4K ; 
 int add_extent_mapping (struct extent_map_tree*,struct extent_map*,int /*<<< orphan*/ ) ; 
 struct extent_map* alloc_extent_map () ; 
 int btrfs_add_extent_mapping (struct btrfs_fs_info*,struct extent_map_tree*,struct extent_map**,scalar_t__,void*) ; 
 scalar_t__ extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map_tree (struct extent_map_tree*) ; 
 int /*<<< orphan*/  test_err (char*,int,...) ; 

__attribute__((used)) static void test_case_2(struct btrfs_fs_info *fs_info,
		struct extent_map_tree *em_tree)
{
	struct extent_map *em;
	int ret;

	em = alloc_extent_map();
	if (!em)
		/* Skip the test on error. */
		return;

	/* Add [0, 1K) */
	em->start = 0;
	em->len = SZ_1K;
	em->block_start = EXTENT_MAP_INLINE;
	em->block_len = (u64)-1;
	ret = add_extent_mapping(em_tree, em, 0);
	ASSERT(ret == 0);
	free_extent_map(em);

	/* Add [4K, 4K) following [0, 1K)  */
	em = alloc_extent_map();
	if (!em)
		goto out;

	em->start = SZ_4K;
	em->len = SZ_4K;
	em->block_start = SZ_4K;
	em->block_len = SZ_4K;
	ret = add_extent_mapping(em_tree, em, 0);
	ASSERT(ret == 0);
	free_extent_map(em);

	em = alloc_extent_map();
	if (!em)
		goto out;

	/* Add [0, 1K) */
	em->start = 0;
	em->len = SZ_1K;
	em->block_start = EXTENT_MAP_INLINE;
	em->block_len = (u64)-1;
	ret = btrfs_add_extent_mapping(fs_info, em_tree, &em, em->start, em->len);
	if (ret)
		test_err("case2 [0 1K]: ret %d", ret);
	if (em &&
	    (em->start != 0 || extent_map_end(em) != SZ_1K ||
	     em->block_start != EXTENT_MAP_INLINE || em->block_len != (u64)-1))
		test_err(
"case2 [0 1K]: ret %d return a wrong em (start %llu len %llu block_start %llu block_len %llu",
			 ret, em->start, em->len, em->block_start,
			 em->block_len);
	free_extent_map(em);
out:
	/* free memory */
	free_extent_map_tree(em_tree);
}