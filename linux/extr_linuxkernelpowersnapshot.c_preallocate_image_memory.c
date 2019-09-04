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

/* Variables and functions */
 int /*<<< orphan*/  GFP_IMAGE ; 
 unsigned long alloc_normal ; 
 unsigned long preallocate_image_pages (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long preallocate_image_memory(unsigned long nr_pages,
					      unsigned long avail_normal)
{
	unsigned long alloc;

	if (avail_normal <= alloc_normal)
		return 0;

	alloc = avail_normal - alloc_normal;
	if (nr_pages < alloc)
		alloc = nr_pages;

	return preallocate_image_pages(alloc, GFP_IMAGE);
}