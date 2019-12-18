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
struct reiserfs_journal {int /*<<< orphan*/  j_dirty_buffers_lock; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {struct buffer_head* b_this_page; scalar_t__ b_private; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  PageChecked (struct page*) ; 
 struct reiserfs_journal* SB_JOURNAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 struct buffer_head* page_buffers (struct page*) ; 
 int /*<<< orphan*/  reiserfs_free_jh (struct buffer_head*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int try_to_free_buffers (struct page*) ; 

__attribute__((used)) static int reiserfs_releasepage(struct page *page, gfp_t unused_gfp_flags)
{
	struct inode *inode = page->mapping->host;
	struct reiserfs_journal *j = SB_JOURNAL(inode->i_sb);
	struct buffer_head *head;
	struct buffer_head *bh;
	int ret = 1;

	WARN_ON(PageChecked(page));
	spin_lock(&j->j_dirty_buffers_lock);
	head = page_buffers(page);
	bh = head;
	do {
		if (bh->b_private) {
			if (!buffer_dirty(bh) && !buffer_locked(bh)) {
				reiserfs_free_jh(bh);
			} else {
				ret = 0;
				break;
			}
		}
		bh = bh->b_this_page;
	} while (bh != head);
	if (ret)
		ret = try_to_free_buffers(page);
	spin_unlock(&j->j_dirty_buffers_lock);
	return ret;
}