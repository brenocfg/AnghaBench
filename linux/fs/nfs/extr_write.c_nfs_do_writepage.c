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
struct writeback_control {int dummy; } ;
struct page {int dummy; } ;
struct nfs_pageio_descriptor {int dummy; } ;

/* Variables and functions */
 int AOP_WRITEPAGE_ACTIVATE ; 
 int EAGAIN ; 
 int nfs_page_async_flush (struct nfs_pageio_descriptor*,struct page*) ; 
 int /*<<< orphan*/  nfs_pageio_cond_complete (struct nfs_pageio_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_index (struct page*) ; 
 int /*<<< orphan*/  redirty_page_for_writepage (struct writeback_control*,struct page*) ; 

__attribute__((used)) static int nfs_do_writepage(struct page *page, struct writeback_control *wbc,
			    struct nfs_pageio_descriptor *pgio)
{
	int ret;

	nfs_pageio_cond_complete(pgio, page_index(page));
	ret = nfs_page_async_flush(pgio, page);
	if (ret == -EAGAIN) {
		redirty_page_for_writepage(wbc, page);
		ret = AOP_WRITEPAGE_ACTIVATE;
	}
	return ret;
}