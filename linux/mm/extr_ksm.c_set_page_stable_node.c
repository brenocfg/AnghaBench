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
struct stable_node {int dummy; } ;
struct page {void* mapping; } ;

/* Variables and functions */
 unsigned long PAGE_MAPPING_KSM ; 

__attribute__((used)) static inline void set_page_stable_node(struct page *page,
					struct stable_node *stable_node)
{
	page->mapping = (void *)((unsigned long)stable_node | PAGE_MAPPING_KSM);
}