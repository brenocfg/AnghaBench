#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {TYPE_1__* mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 scalar_t__ bdi_cap_stable_pages_required (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_to_bdi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_page_writeback (struct page*) ; 

void wait_for_stable_page(struct page *page)
{
	if (bdi_cap_stable_pages_required(inode_to_bdi(page->mapping->host)))
		wait_on_page_writeback(page);
}