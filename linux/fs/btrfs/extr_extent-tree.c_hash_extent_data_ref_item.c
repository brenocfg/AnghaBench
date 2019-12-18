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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {int dummy; } ;
struct btrfs_extent_data_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_extent_data_ref_objectid (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 int /*<<< orphan*/  btrfs_extent_data_ref_offset (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 int /*<<< orphan*/  btrfs_extent_data_ref_root (struct extent_buffer*,struct btrfs_extent_data_ref*) ; 
 int /*<<< orphan*/  hash_extent_data_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 hash_extent_data_ref_item(struct extent_buffer *leaf,
				     struct btrfs_extent_data_ref *ref)
{
	return hash_extent_data_ref(btrfs_extent_data_ref_root(leaf, ref),
				    btrfs_extent_data_ref_objectid(leaf, ref),
				    btrfs_extent_data_ref_offset(leaf, ref));
}