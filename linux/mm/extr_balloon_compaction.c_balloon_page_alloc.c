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
 int __GFP_NOMEMALLOC ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 struct page* alloc_page (int) ; 
 int balloon_mapping_gfp_mask () ; 

struct page *balloon_page_alloc(void)
{
	struct page *page = alloc_page(balloon_mapping_gfp_mask() |
				       __GFP_NOMEMALLOC | __GFP_NORETRY |
				       __GFP_NOWARN);
	return page;
}