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
struct page {int dummy; } ;
struct iomap {int flags; } ;
struct inode {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int IOMAP_F_BUFFER_HEAD ; 
 int /*<<< orphan*/  PageUptodate (struct page*) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int __block_write_begin_int (struct page*,int,int,int /*<<< orphan*/ *,struct iomap*) ; 
 int /*<<< orphan*/  block_commit_write (struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iomap_page_create (struct inode*,struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

__attribute__((used)) static loff_t
iomap_page_mkwrite_actor(struct inode *inode, loff_t pos, loff_t length,
		void *data, struct iomap *iomap)
{
	struct page *page = data;
	int ret;

	if (iomap->flags & IOMAP_F_BUFFER_HEAD) {
		ret = __block_write_begin_int(page, pos, length, NULL, iomap);
		if (ret)
			return ret;
		block_commit_write(page, 0, length);
	} else {
		WARN_ON_ONCE(!PageUptodate(page));
		iomap_page_create(inode, page);
		set_page_dirty(page);
	}

	return length;
}