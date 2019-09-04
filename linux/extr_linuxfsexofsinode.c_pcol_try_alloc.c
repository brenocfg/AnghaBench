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
struct page_collect {unsigned int alloc_pages; int /*<<< orphan*/  expected_pages; int /*<<< orphan*/  pages; TYPE_1__* sbi; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EXOFS_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int exofs_max_io_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcol_try_alloc(struct page_collect *pcol)
{
	unsigned pages;

	/* TODO: easily support bio chaining */
	pages =  exofs_max_io_pages(&pcol->sbi->layout, pcol->expected_pages);

	for (; pages; pages >>= 1) {
		pcol->pages = kmalloc_array(pages, sizeof(struct page *),
					    GFP_KERNEL);
		if (likely(pcol->pages)) {
			pcol->alloc_pages = pages;
			return 0;
		}
	}

	EXOFS_ERR("Failed to kmalloc expected_pages=%u\n",
		  pcol->expected_pages);
	return -ENOMEM;
}