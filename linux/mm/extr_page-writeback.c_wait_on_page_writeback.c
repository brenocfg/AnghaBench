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
 int /*<<< orphan*/  PG_writeback ; 
 scalar_t__ PageWriteback (struct page*) ; 
 int /*<<< orphan*/  page_mapping (struct page*) ; 
 int /*<<< orphan*/  trace_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_page_bit (struct page*,int /*<<< orphan*/ ) ; 

void wait_on_page_writeback(struct page *page)
{
	if (PageWriteback(page)) {
		trace_wait_on_page_writeback(page, page_mapping(page));
		wait_on_page_bit(page, PG_writeback);
	}
}