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
struct iomap {scalar_t__ type; int flags; int /*<<< orphan*/  (* page_done ) (struct inode*,int /*<<< orphan*/ ,unsigned int,struct page*,struct iomap*) ;} ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int IOMAP_F_BUFFER_HEAD ; 
 scalar_t__ IOMAP_INLINE ; 
 int __iomap_write_end (struct inode*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page*,struct iomap*) ; 
 int generic_write_end (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page*,int /*<<< orphan*/ *) ; 
 int iomap_write_end_inline (struct inode*,struct page*,struct iomap*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  iomap_write_failed (struct inode*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct inode*,int /*<<< orphan*/ ,unsigned int,struct page*,struct iomap*) ; 

__attribute__((used)) static int
iomap_write_end(struct inode *inode, loff_t pos, unsigned len,
		unsigned copied, struct page *page, struct iomap *iomap)
{
	int ret;

	if (iomap->type == IOMAP_INLINE) {
		ret = iomap_write_end_inline(inode, page, iomap, pos, copied);
	} else if (iomap->flags & IOMAP_F_BUFFER_HEAD) {
		ret = generic_write_end(NULL, inode->i_mapping, pos, len,
				copied, page, NULL);
	} else {
		ret = __iomap_write_end(inode, pos, len, copied, page, iomap);
	}

	if (iomap->page_done)
		iomap->page_done(inode, pos, copied, page, iomap);

	if (ret < len)
		iomap_write_failed(inode, pos, len);
	return ret;
}