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
typedef  int u64 ;
struct page {int dummy; } ;
struct inode {int dummy; } ;
typedef  int pgoff_t ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct page*) ; 
 struct page* extent_same_get_page (struct inode*,int) ; 

__attribute__((used)) static int gather_extent_pages(struct inode *inode, struct page **pages,
			       int num_pages, u64 off)
{
	int i;
	pgoff_t index = off >> PAGE_SHIFT;

	for (i = 0; i < num_pages; i++) {
again:
		pages[i] = extent_same_get_page(inode, index + i);
		if (IS_ERR(pages[i])) {
			int err = PTR_ERR(pages[i]);

			if (err == -EAGAIN)
				goto again;
			pages[i] = NULL;
			return err;
		}
	}
	return 0;
}