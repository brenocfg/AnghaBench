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
typedef  int sector_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 scalar_t__ __page_file_index (struct page*) ; 

__attribute__((used)) static sector_t swap_page_sector(struct page *page)
{
	return (sector_t)__page_file_index(page) << (PAGE_SHIFT - 9);
}