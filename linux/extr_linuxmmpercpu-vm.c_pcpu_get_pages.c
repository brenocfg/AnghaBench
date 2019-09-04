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
typedef  int /*<<< orphan*/  pages ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcpu_alloc_mutex ; 
 struct page** pcpu_mem_zalloc (size_t,int /*<<< orphan*/ ) ; 
 int pcpu_nr_units ; 
 int pcpu_unit_pages ; 

__attribute__((used)) static struct page **pcpu_get_pages(void)
{
	static struct page **pages;
	size_t pages_size = pcpu_nr_units * pcpu_unit_pages * sizeof(pages[0]);

	lockdep_assert_held(&pcpu_alloc_mutex);

	if (!pages)
		pages = pcpu_mem_zalloc(pages_size, GFP_KERNEL);
	return pages;
}