#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int /*<<< orphan*/  flags; int /*<<< orphan*/  index; struct address_space* mapping; } ;
struct cachefiles_one_read {int /*<<< orphan*/  op_link; int /*<<< orphan*/  monitor; struct page* back_page; } ;
struct cachefiles_object {int /*<<< orphan*/  work_lock; int /*<<< orphan*/  backer; } ;
struct address_space {TYPE_1__* a_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ino; struct address_space* i_mapping; } ;
struct TYPE_3__ {int (* readpage ) (int /*<<< orphan*/ *,struct page*) ;} ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EIO ; 
 int ENODATA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ PageError (struct page*) ; 
 scalar_t__ PageUptodate (struct page*) ; 
 int /*<<< orphan*/  _debug (char*,...) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  add_page_wait_queue (struct page*,int /*<<< orphan*/ *) ; 
 TYPE_2__* d_backing_inode (int /*<<< orphan*/ ) ; 
 struct page* find_get_page (struct address_space*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *,struct page*) ; 
 scalar_t__ trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int cachefiles_read_reissue(struct cachefiles_object *object,
				   struct cachefiles_one_read *monitor)
{
	struct address_space *bmapping = d_backing_inode(object->backer)->i_mapping;
	struct page *backpage = monitor->back_page, *backpage2;
	int ret;

	_enter("{ino=%lx},{%lx,%lx}",
	       d_backing_inode(object->backer)->i_ino,
	       backpage->index, backpage->flags);

	/* skip if the page was truncated away completely */
	if (backpage->mapping != bmapping) {
		_leave(" = -ENODATA [mapping]");
		return -ENODATA;
	}

	backpage2 = find_get_page(bmapping, backpage->index);
	if (!backpage2) {
		_leave(" = -ENODATA [gone]");
		return -ENODATA;
	}

	if (backpage != backpage2) {
		put_page(backpage2);
		_leave(" = -ENODATA [different]");
		return -ENODATA;
	}

	/* the page is still there and we already have a ref on it, so we don't
	 * need a second */
	put_page(backpage2);

	INIT_LIST_HEAD(&monitor->op_link);
	add_page_wait_queue(backpage, &monitor->monitor);

	if (trylock_page(backpage)) {
		ret = -EIO;
		if (PageError(backpage))
			goto unlock_discard;
		ret = 0;
		if (PageUptodate(backpage))
			goto unlock_discard;

		_debug("reissue read");
		ret = bmapping->a_ops->readpage(NULL, backpage);
		if (ret < 0)
			goto unlock_discard;
	}

	/* but the page may have been read before the monitor was installed, so
	 * the monitor may miss the event - so we have to ensure that we do get
	 * one in such a case */
	if (trylock_page(backpage)) {
		_debug("jumpstart %p {%lx}", backpage, backpage->flags);
		unlock_page(backpage);
	}

	/* it'll reappear on the todo list */
	_leave(" = -EINPROGRESS");
	return -EINPROGRESS;

unlock_discard:
	unlock_page(backpage);
	spin_lock_irq(&object->work_lock);
	list_del(&monitor->op_link);
	spin_unlock_irq(&object->work_lock);
	_leave(" = %d", ret);
	return ret;
}