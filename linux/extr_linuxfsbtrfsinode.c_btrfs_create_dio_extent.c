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
struct inode {int dummy; } ;
struct extent_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_COMPRESS_NONE ; 
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 int const BTRFS_ORDERED_NOCOW ; 
 struct extent_map* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 int btrfs_add_ordered_extent_dio (struct inode*,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,int const) ; 
 int /*<<< orphan*/  btrfs_drop_extent_cache (int /*<<< orphan*/ ,scalar_t__ const,scalar_t__ const,int /*<<< orphan*/ ) ; 
 struct extent_map* create_io_em (struct inode*,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,scalar_t__ const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 

__attribute__((used)) static struct extent_map *btrfs_create_dio_extent(struct inode *inode,
						  const u64 start,
						  const u64 len,
						  const u64 orig_start,
						  const u64 block_start,
						  const u64 block_len,
						  const u64 orig_block_len,
						  const u64 ram_bytes,
						  const int type)
{
	struct extent_map *em = NULL;
	int ret;

	if (type != BTRFS_ORDERED_NOCOW) {
		em = create_io_em(inode, start, len, orig_start,
				  block_start, block_len, orig_block_len,
				  ram_bytes,
				  BTRFS_COMPRESS_NONE, /* compress_type */
				  type);
		if (IS_ERR(em))
			goto out;
	}
	ret = btrfs_add_ordered_extent_dio(inode, start, block_start,
					   len, block_len, type);
	if (ret) {
		if (em) {
			free_extent_map(em);
			btrfs_drop_extent_cache(BTRFS_I(inode), start,
						start + len - 1, 0);
		}
		em = ERR_PTR(ret);
	}
 out:

	return em;
}