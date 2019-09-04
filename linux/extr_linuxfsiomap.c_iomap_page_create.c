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
struct iomap_page {int /*<<< orphan*/  uptodate; int /*<<< orphan*/  write_count; int /*<<< orphan*/  read_count; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int GFP_NOFS ; 
 int PAGE_SIZE ; 
 int SECTOR_SIZE ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int i_blocksize (struct inode*) ; 
 struct iomap_page* kmalloc (int,int) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 struct iomap_page* to_iomap_page (struct page*) ; 

__attribute__((used)) static struct iomap_page *
iomap_page_create(struct inode *inode, struct page *page)
{
	struct iomap_page *iop = to_iomap_page(page);

	if (iop || i_blocksize(inode) == PAGE_SIZE)
		return iop;

	iop = kmalloc(sizeof(*iop), GFP_NOFS | __GFP_NOFAIL);
	atomic_set(&iop->read_count, 0);
	atomic_set(&iop->write_count, 0);
	bitmap_zero(iop->uptodate, PAGE_SIZE / SECTOR_SIZE);

	/*
	 * migrate_page_move_mapping() assumes that pages with private data have
	 * their count elevated by 1.
	 */
	get_page(page);
	set_page_private(page, (unsigned long)iop);
	SetPagePrivate(page);
	return iop;
}