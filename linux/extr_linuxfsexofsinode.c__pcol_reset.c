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
struct page_collect {int pg_first; TYPE_1__* sbi; scalar_t__ expected_pages; int /*<<< orphan*/ * that_locked_page; int /*<<< orphan*/ * ios; scalar_t__ length; scalar_t__ nr_pages; scalar_t__ alloc_pages; int /*<<< orphan*/ * pages; } ;
struct TYPE_2__ {int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 scalar_t__ exofs_max_io_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void _pcol_reset(struct page_collect *pcol)
{
	pcol->expected_pages -= min(pcol->nr_pages, pcol->expected_pages);

	pcol->pages = NULL;
	pcol->alloc_pages = 0;
	pcol->nr_pages = 0;
	pcol->length = 0;
	pcol->pg_first = -1;
	pcol->ios = NULL;
	pcol->that_locked_page = NULL;

	/* this is probably the end of the loop but in writes
	 * it might not end here. don't be left with nothing
	 */
	if (!pcol->expected_pages)
		pcol->expected_pages =
				exofs_max_io_pages(&pcol->sbi->layout, ~0);
}