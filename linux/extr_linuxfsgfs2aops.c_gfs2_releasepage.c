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
struct page {struct address_space* mapping; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_ail_lock; } ;
struct gfs2_bufdata {struct buffer_head* bd_bh; int /*<<< orphan*/  bd_list; scalar_t__ bd_tr; } ;
struct buffer_head {struct buffer_head* b_this_page; struct gfs2_bufdata* b_private; int /*<<< orphan*/  b_count; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_pinned (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_assert_warn (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_bufdata_cachep ; 
 int /*<<< orphan*/  gfs2_log_lock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_unlock (struct gfs2_sbd*) ; 
 struct gfs2_sbd* gfs2_mapping2sbd (struct address_space*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct gfs2_bufdata*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  page_has_buffers (struct page*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int try_to_free_buffers (struct page*) ; 

int gfs2_releasepage(struct page *page, gfp_t gfp_mask)
{
	struct address_space *mapping = page->mapping;
	struct gfs2_sbd *sdp = gfs2_mapping2sbd(mapping);
	struct buffer_head *bh, *head;
	struct gfs2_bufdata *bd;

	if (!page_has_buffers(page))
		return 0;

	/*
	 * From xfs_vm_releasepage: mm accommodates an old ext3 case where
	 * clean pages might not have had the dirty bit cleared.  Thus, it can
	 * send actual dirty pages to ->releasepage() via shrink_active_list().
	 *
	 * As a workaround, we skip pages that contain dirty buffers below.
	 * Once ->releasepage isn't called on dirty pages anymore, we can warn
	 * on dirty buffers like we used to here again.
	 */

	gfs2_log_lock(sdp);
	spin_lock(&sdp->sd_ail_lock);
	head = bh = page_buffers(page);
	do {
		if (atomic_read(&bh->b_count))
			goto cannot_release;
		bd = bh->b_private;
		if (bd && bd->bd_tr)
			goto cannot_release;
		if (buffer_dirty(bh) || WARN_ON(buffer_pinned(bh)))
			goto cannot_release;
		bh = bh->b_this_page;
	} while(bh != head);
	spin_unlock(&sdp->sd_ail_lock);

	head = bh = page_buffers(page);
	do {
		bd = bh->b_private;
		if (bd) {
			gfs2_assert_warn(sdp, bd->bd_bh == bh);
			if (!list_empty(&bd->bd_list))
				list_del_init(&bd->bd_list);
			bd->bd_bh = NULL;
			bh->b_private = NULL;
			kmem_cache_free(gfs2_bufdata_cachep, bd);
		}

		bh = bh->b_this_page;
	} while (bh != head);
	gfs2_log_unlock(sdp);

	return try_to_free_buffers(page);

cannot_release:
	spin_unlock(&sdp->sd_ail_lock);
	gfs2_log_unlock(sdp);
	return 0;
}