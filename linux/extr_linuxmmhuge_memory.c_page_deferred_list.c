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
struct list_head {int dummy; } ;
struct page {struct list_head deferred_list; } ;

/* Variables and functions */

__attribute__((used)) static inline struct list_head *page_deferred_list(struct page *page)
{
	/* ->lru in the tail pages is occupied by compound_head. */
	return &page[2].deferred_list;
}