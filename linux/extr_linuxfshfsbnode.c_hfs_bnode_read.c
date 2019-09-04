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
struct hfs_bnode {struct page** page; scalar_t__ page_offset; } ;

/* Variables and functions */
 scalar_t__ kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,int) ; 

void hfs_bnode_read(struct hfs_bnode *node, void *buf,
		int off, int len)
{
	struct page *page;

	off += node->page_offset;
	page = node->page[0];

	memcpy(buf, kmap(page) + off, len);
	kunmap(page);
}