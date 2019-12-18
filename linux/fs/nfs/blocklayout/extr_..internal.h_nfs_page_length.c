#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
typedef  scalar_t__ pgoff_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 unsigned int PAGE_SIZE ; 
 int i_size_read (int /*<<< orphan*/ ) ; 
 TYPE_1__* page_file_mapping (struct page*) ; 
 scalar_t__ page_index (struct page*) ; 

__attribute__((used)) static inline
unsigned int nfs_page_length(struct page *page)
{
	loff_t i_size = i_size_read(page_file_mapping(page)->host);

	if (i_size > 0) {
		pgoff_t index = page_index(page);
		pgoff_t end_index = (i_size - 1) >> PAGE_SHIFT;
		if (index < end_index)
			return PAGE_SIZE;
		if (index == end_index)
			return ((i_size - 1) & ~PAGE_MASK) + 1;
	}
	return 0;
}