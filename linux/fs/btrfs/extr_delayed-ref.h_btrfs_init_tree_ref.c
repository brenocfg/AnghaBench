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
typedef  void* u64 ;
struct TYPE_2__ {int level; void* root; } ;
struct btrfs_ref {int /*<<< orphan*/  type; TYPE_1__ tree_ref; void* real_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_REF_METADATA ; 

__attribute__((used)) static inline void btrfs_init_tree_ref(struct btrfs_ref *generic_ref,
				int level, u64 root)
{
	/* If @real_root not set, use @root as fallback */
	if (!generic_ref->real_root)
		generic_ref->real_root = root;
	generic_ref->tree_ref.level = level;
	generic_ref->tree_ref.root = root;
	generic_ref->type = BTRFS_REF_METADATA;
}