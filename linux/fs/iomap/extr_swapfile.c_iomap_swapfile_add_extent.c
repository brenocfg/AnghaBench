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
typedef  int uint64_t ;
struct iomap {scalar_t__ offset; scalar_t__ length; scalar_t__ addr; } ;
struct iomap_swapfile_info {int lowest_ppage; int highest_ppage; unsigned long nr_pages; int nr_extents; int /*<<< orphan*/  sis; struct iomap iomap; } ;

/* Variables and functions */
 int ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int ALIGN_DOWN (scalar_t__,int /*<<< orphan*/ ) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int add_swap_extent (int /*<<< orphan*/ ,unsigned long,unsigned long,int) ; 

__attribute__((used)) static int iomap_swapfile_add_extent(struct iomap_swapfile_info *isi)
{
	struct iomap *iomap = &isi->iomap;
	unsigned long nr_pages;
	uint64_t first_ppage;
	uint64_t first_ppage_reported;
	uint64_t next_ppage;
	int error;

	/*
	 * Round the start up and the end down so that the physical
	 * extent aligns to a page boundary.
	 */
	first_ppage = ALIGN(iomap->addr, PAGE_SIZE) >> PAGE_SHIFT;
	next_ppage = ALIGN_DOWN(iomap->addr + iomap->length, PAGE_SIZE) >>
			PAGE_SHIFT;

	/* Skip too-short physical extents. */
	if (first_ppage >= next_ppage)
		return 0;
	nr_pages = next_ppage - first_ppage;

	/*
	 * Calculate how much swap space we're adding; the first page contains
	 * the swap header and doesn't count.  The mm still wants that first
	 * page fed to add_swap_extent, however.
	 */
	first_ppage_reported = first_ppage;
	if (iomap->offset == 0)
		first_ppage_reported++;
	if (isi->lowest_ppage > first_ppage_reported)
		isi->lowest_ppage = first_ppage_reported;
	if (isi->highest_ppage < (next_ppage - 1))
		isi->highest_ppage = next_ppage - 1;

	/* Add extent, set up for the next call. */
	error = add_swap_extent(isi->sis, isi->nr_pages, nr_pages, first_ppage);
	if (error < 0)
		return error;
	isi->nr_extents += error;
	isi->nr_pages += nr_pages;
	return 0;
}