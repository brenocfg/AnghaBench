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
struct page {int /*<<< orphan*/  mem_cgroup; } ;

/* Variables and functions */
 int /*<<< orphan*/  __unlock_page_memcg (int /*<<< orphan*/ ) ; 

void unlock_page_memcg(struct page *page)
{
	__unlock_page_memcg(page->mem_cgroup);
}