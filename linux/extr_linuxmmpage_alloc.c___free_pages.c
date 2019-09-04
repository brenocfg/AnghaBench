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

/* Variables and functions */
 int /*<<< orphan*/  __free_pages_ok (struct page*,unsigned int) ; 
 int /*<<< orphan*/  free_unref_page (struct page*) ; 
 scalar_t__ put_page_testzero (struct page*) ; 

void __free_pages(struct page *page, unsigned int order)
{
	if (put_page_testzero(page)) {
		if (order == 0)
			free_unref_page(page);
		else
			__free_pages_ok(page, order);
	}
}