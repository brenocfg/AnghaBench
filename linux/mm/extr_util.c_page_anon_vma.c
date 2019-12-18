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
struct page {scalar_t__ mapping; } ;
struct anon_vma {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MAPPING_ANON ; 
 unsigned long PAGE_MAPPING_FLAGS ; 
 struct anon_vma* __page_rmapping (struct page*) ; 
 struct page* compound_head (struct page*) ; 

struct anon_vma *page_anon_vma(struct page *page)
{
	unsigned long mapping;

	page = compound_head(page);
	mapping = (unsigned long)page->mapping;
	if ((mapping & PAGE_MAPPING_FLAGS) != PAGE_MAPPING_ANON)
		return NULL;
	return __page_rmapping(page);
}