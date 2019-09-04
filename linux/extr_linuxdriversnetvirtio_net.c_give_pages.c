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
struct receive_queue {struct page* pages; } ;
struct page {long private; } ;

/* Variables and functions */

__attribute__((used)) static void give_pages(struct receive_queue *rq, struct page *page)
{
	struct page *end;

	/* Find end of list, sew whole thing into vi->rq.pages. */
	for (end = page; end->private; end = (struct page *)end->private);
	end->private = (unsigned long)rq->pages;
	rq->pages = page;
}