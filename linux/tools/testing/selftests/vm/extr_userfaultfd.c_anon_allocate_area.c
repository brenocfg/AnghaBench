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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int nr_pages ; 
 int page_size ; 
 scalar_t__ posix_memalign (void**,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void anon_allocate_area(void **alloc_area)
{
	if (posix_memalign(alloc_area, page_size, nr_pages * page_size)) {
		fprintf(stderr, "out of memory\n");
		*alloc_area = NULL;
	}
}