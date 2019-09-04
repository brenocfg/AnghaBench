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
struct page_collect {scalar_t__ nr_pages; scalar_t__ alloc_pages; int /*<<< orphan*/  length; struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int pcol_add_page(struct page_collect *pcol, struct page *page,
			 unsigned len)
{
	if (unlikely(pcol->nr_pages >= pcol->alloc_pages))
		return -ENOMEM;

	pcol->pages[pcol->nr_pages++] = page;
	pcol->length += len;
	return 0;
}