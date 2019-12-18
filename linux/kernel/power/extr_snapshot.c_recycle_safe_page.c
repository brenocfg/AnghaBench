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
struct linked_page {struct linked_page* next; } ;

/* Variables and functions */
 struct linked_page* safe_pages_list ; 

__attribute__((used)) static void recycle_safe_page(void *page_address)
{
	struct linked_page *lp = page_address;

	lp->next = safe_pages_list;
	safe_pages_list = lp;
}