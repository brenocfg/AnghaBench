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
struct ocfs2_meta_cache_item {int dummy; } ;
struct ocfs2_caching_info {int ci_flags; int /*<<< orphan*/  ci_num_cached; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int OCFS2_CACHE_FL_INLINE ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ocfs2_meta_cache_item*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_lock (struct ocfs2_caching_info*) ; 
 scalar_t__ ocfs2_metadata_cache_owner (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_metadata_cache_unlock (struct ocfs2_caching_info*) ; 
 int /*<<< orphan*/  ocfs2_remove_metadata_array (struct ocfs2_caching_info*,int) ; 
 int /*<<< orphan*/  ocfs2_remove_metadata_tree (struct ocfs2_caching_info*,struct ocfs2_meta_cache_item*) ; 
 int ocfs2_search_cache_array (struct ocfs2_caching_info*,scalar_t__) ; 
 struct ocfs2_meta_cache_item* ocfs2_search_cache_tree (struct ocfs2_caching_info*,scalar_t__) ; 
 int /*<<< orphan*/  ocfs2_uptodate_cachep ; 
 int /*<<< orphan*/  trace_ocfs2_remove_block_from_cache (unsigned long long,unsigned long long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocfs2_remove_block_from_cache(struct ocfs2_caching_info *ci,
					  sector_t block)
{
	int index;
	struct ocfs2_meta_cache_item *item = NULL;

	ocfs2_metadata_cache_lock(ci);
	trace_ocfs2_remove_block_from_cache(
		(unsigned long long)ocfs2_metadata_cache_owner(ci),
		(unsigned long long) block, ci->ci_num_cached,
		ci->ci_flags);

	if (ci->ci_flags & OCFS2_CACHE_FL_INLINE) {
		index = ocfs2_search_cache_array(ci, block);
		if (index != -1)
			ocfs2_remove_metadata_array(ci, index);
	} else {
		item = ocfs2_search_cache_tree(ci, block);
		if (item)
			ocfs2_remove_metadata_tree(ci, item);
	}
	ocfs2_metadata_cache_unlock(ci);

	if (item)
		kmem_cache_free(ocfs2_uptodate_cachep, item);
}