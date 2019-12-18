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
 int /*<<< orphan*/  __dump_page (struct page*,char const*) ; 
 int /*<<< orphan*/  dump_page_owner (struct page*) ; 

void dump_page(struct page *page, const char *reason)
{
	__dump_page(page, reason);
	dump_page_owner(page);
}