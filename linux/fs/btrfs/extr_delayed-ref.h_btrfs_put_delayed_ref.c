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
struct btrfs_delayed_ref_node {int in_tree; int type; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
#define  BTRFS_EXTENT_DATA_REF_KEY 131 
#define  BTRFS_SHARED_BLOCK_REF_KEY 130 
#define  BTRFS_SHARED_DATA_REF_KEY 129 
#define  BTRFS_TREE_BLOCK_REF_KEY 128 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  btrfs_delayed_data_ref_cachep ; 
 int /*<<< orphan*/  btrfs_delayed_tree_ref_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct btrfs_delayed_ref_node*) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void btrfs_put_delayed_ref(struct btrfs_delayed_ref_node *ref)
{
	WARN_ON(refcount_read(&ref->refs) == 0);
	if (refcount_dec_and_test(&ref->refs)) {
		WARN_ON(ref->in_tree);
		switch (ref->type) {
		case BTRFS_TREE_BLOCK_REF_KEY:
		case BTRFS_SHARED_BLOCK_REF_KEY:
			kmem_cache_free(btrfs_delayed_tree_ref_cachep, ref);
			break;
		case BTRFS_EXTENT_DATA_REF_KEY:
		case BTRFS_SHARED_DATA_REF_KEY:
			kmem_cache_free(btrfs_delayed_data_ref_cachep, ref);
			break;
		default:
			BUG();
		}
	}
}