#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {scalar_t__ root; } ;
struct btrfs_ref {scalar_t__ type; TYPE_1__ tree_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_DATA ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_METADATA ; 
 int /*<<< orphan*/  BTRFS_BLOCK_GROUP_SYSTEM ; 
 scalar_t__ BTRFS_CHUNK_TREE_OBJECTID ; 
 scalar_t__ BTRFS_REF_METADATA ; 

__attribute__((used)) static u64 generic_ref_to_space_flags(struct btrfs_ref *ref)
{
	if (ref->type == BTRFS_REF_METADATA) {
		if (ref->tree_ref.root == BTRFS_CHUNK_TREE_OBJECTID)
			return BTRFS_BLOCK_GROUP_SYSTEM;
		else
			return BTRFS_BLOCK_GROUP_METADATA;
	}
	return BTRFS_BLOCK_GROUP_DATA;
}