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
struct super_block {int dummy; } ;
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_lock; struct super_block* rf_sb; int /*<<< orphan*/  rf_io_mutex; int /*<<< orphan*/  rf_ci; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_refcount_caching_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ocfs2_init_refcount_tree_ci(struct ocfs2_refcount_tree *new,
					       struct super_block *sb)
{
	ocfs2_metadata_cache_init(&new->rf_ci, &ocfs2_refcount_caching_ops);
	mutex_init(&new->rf_io_mutex);
	new->rf_sb = sb;
	spin_lock_init(&new->rf_lock);
}