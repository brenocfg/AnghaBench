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
struct page {int const index; } ;
typedef  int s64 ;
typedef  int loff_t ;

/* Variables and functions */
 int const PAGE_SHIFT ; 
 int /*<<< orphan*/  zero_partial_compressed_page (struct page*,int const) ; 

__attribute__((used)) static inline void handle_bounds_compressed_page(struct page *page,
		const loff_t i_size, const s64 initialized_size)
{
	if ((page->index >= (initialized_size >> PAGE_SHIFT)) &&
			(initialized_size < i_size))
		zero_partial_compressed_page(page, initialized_size);
	return;
}