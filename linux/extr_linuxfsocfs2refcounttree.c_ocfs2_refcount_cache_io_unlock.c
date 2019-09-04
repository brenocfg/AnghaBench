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
struct ocfs2_refcount_tree {int /*<<< orphan*/  rf_io_mutex; } ;
struct ocfs2_caching_info {int dummy; } ;

/* Variables and functions */
 struct ocfs2_refcount_tree* cache_info_to_refcount (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_refcount_cache_io_unlock(struct ocfs2_caching_info *ci)
{
	struct ocfs2_refcount_tree *rf = cache_info_to_refcount(ci);

	mutex_unlock(&rf->rf_io_mutex);
}