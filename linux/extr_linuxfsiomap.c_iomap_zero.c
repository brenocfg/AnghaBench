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
struct iomap {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOP_FLAG_NOFS ; 
 int iomap_write_begin (struct inode*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct page**,struct iomap*) ; 
 int iomap_write_end (struct inode*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page*,struct iomap*) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  zero_user (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static int iomap_zero(struct inode *inode, loff_t pos, unsigned offset,
		unsigned bytes, struct iomap *iomap)
{
	struct page *page;
	int status;

	status = iomap_write_begin(inode, pos, bytes, AOP_FLAG_NOFS, &page,
				   iomap);
	if (status)
		return status;

	zero_user(page, offset, bytes);
	mark_page_accessed(page);

	return iomap_write_end(inode, pos, bytes, bytes, page, iomap);
}