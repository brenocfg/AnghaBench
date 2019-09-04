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
struct ore_layout {unsigned int group_width; unsigned int stripe_unit; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 unsigned int exofs_max_io_pages (struct ore_layout*,int /*<<< orphan*/ ) ; 
 unsigned int roundup (unsigned int const,unsigned int) ; 

__attribute__((used)) static unsigned __ra_pages(struct ore_layout *layout)
{
	const unsigned _MIN_RA = 32; /* min 128K read-ahead */
	unsigned ra_pages = layout->group_width * layout->stripe_unit /
				PAGE_SIZE;
	unsigned max_io_pages = exofs_max_io_pages(layout, ~0);

	ra_pages *= 2; /* two stripes */
	if (ra_pages < _MIN_RA)
		ra_pages = roundup(_MIN_RA, ra_pages / 2);

	if (ra_pages > max_io_pages)
		ra_pages = max_io_pages;

	return ra_pages;
}