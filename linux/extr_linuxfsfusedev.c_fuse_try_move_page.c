#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pipe_buffer {scalar_t__ len; int flags; int /*<<< orphan*/  offset; struct page* page; } ;
struct page {int dummy; } ;
struct fuse_copy_state {scalar_t__ len; TYPE_2__* req; int /*<<< orphan*/  offset; struct page* pg; int /*<<< orphan*/  pipe; int /*<<< orphan*/  nr_segs; struct pipe_buffer* pipebufs; struct pipe_buffer* currbuf; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {TYPE_1__ waitq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int ENOENT ; 
 int /*<<< orphan*/  FR_ABORTED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 int PIPE_BUF_FLAG_LRU ; 
 scalar_t__ PageDirty (struct page*) ; 
 int PageMlocked (struct page*) ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ fuse_check_page (struct page*) ; 
 int /*<<< orphan*/  fuse_copy_finish (struct fuse_copy_state*) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int lock_request (TYPE_2__*) ; 
 int /*<<< orphan*/  lru_cache_add_file (struct page*) ; 
 int page_has_private (struct page*) ; 
 int page_mapped (struct page*) ; 
 int pipe_buf_confirm (int /*<<< orphan*/ ,struct pipe_buffer*) ; 
 scalar_t__ pipe_buf_steal (int /*<<< orphan*/ ,struct pipe_buffer*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int replace_page_cache_page (struct page*,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int unlock_request (TYPE_2__*) ; 

__attribute__((used)) static int fuse_try_move_page(struct fuse_copy_state *cs, struct page **pagep)
{
	int err;
	struct page *oldpage = *pagep;
	struct page *newpage;
	struct pipe_buffer *buf = cs->pipebufs;

	err = unlock_request(cs->req);
	if (err)
		return err;

	fuse_copy_finish(cs);

	err = pipe_buf_confirm(cs->pipe, buf);
	if (err)
		return err;

	BUG_ON(!cs->nr_segs);
	cs->currbuf = buf;
	cs->len = buf->len;
	cs->pipebufs++;
	cs->nr_segs--;

	if (cs->len != PAGE_SIZE)
		goto out_fallback;

	if (pipe_buf_steal(cs->pipe, buf) != 0)
		goto out_fallback;

	newpage = buf->page;

	if (!PageUptodate(newpage))
		SetPageUptodate(newpage);

	ClearPageMappedToDisk(newpage);

	if (fuse_check_page(newpage) != 0)
		goto out_fallback_unlock;

	/*
	 * This is a new and locked page, it shouldn't be mapped or
	 * have any special flags on it
	 */
	if (WARN_ON(page_mapped(oldpage)))
		goto out_fallback_unlock;
	if (WARN_ON(page_has_private(oldpage)))
		goto out_fallback_unlock;
	if (WARN_ON(PageDirty(oldpage) || PageWriteback(oldpage)))
		goto out_fallback_unlock;
	if (WARN_ON(PageMlocked(oldpage)))
		goto out_fallback_unlock;

	err = replace_page_cache_page(oldpage, newpage, GFP_KERNEL);
	if (err) {
		unlock_page(newpage);
		return err;
	}

	get_page(newpage);

	if (!(buf->flags & PIPE_BUF_FLAG_LRU))
		lru_cache_add_file(newpage);

	err = 0;
	spin_lock(&cs->req->waitq.lock);
	if (test_bit(FR_ABORTED, &cs->req->flags))
		err = -ENOENT;
	else
		*pagep = newpage;
	spin_unlock(&cs->req->waitq.lock);

	if (err) {
		unlock_page(newpage);
		put_page(newpage);
		return err;
	}

	unlock_page(oldpage);
	put_page(oldpage);
	cs->len = 0;

	return 0;

out_fallback_unlock:
	unlock_page(newpage);
out_fallback:
	cs->pg = buf->page;
	cs->offset = buf->offset;

	err = lock_request(cs->req);
	if (err)
		return err;

	return 1;
}