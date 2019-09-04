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
 scalar_t__ PageHead (struct page*) ; 
 int /*<<< orphan*/  PageHuge (struct page*) ; 
 scalar_t__ PagePrivate (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 

bool page_huge_active(struct page *page)
{
	VM_BUG_ON_PAGE(!PageHuge(page), page);
	return PageHead(page) && PagePrivate(&page[1]);
}