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
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area_control ;
typedef  int /*<<< orphan*/  FreePageManager ;

/* Variables and functions */
 size_t FPM_PAGE_SIZE ; 
 size_t MAXALIGN (int) ; 

size_t
dsa_minimum_size(void)
{
	size_t		size;
	int			pages = 0;

	size = MAXALIGN(sizeof(dsa_area_control)) +
		MAXALIGN(sizeof(FreePageManager));

	/* Figure out how many pages we need, including the page map... */
	while (((size + FPM_PAGE_SIZE - 1) / FPM_PAGE_SIZE) > pages)
	{
		++pages;
		size += sizeof(dsa_pointer);
	}

	return pages * FPM_PAGE_SIZE;
}