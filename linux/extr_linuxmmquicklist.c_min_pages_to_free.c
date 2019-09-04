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
struct quicklist {long nr_pages; } ;

/* Variables and functions */
 long max_pages (unsigned long) ; 
 long min (long,long) ; 

__attribute__((used)) static long min_pages_to_free(struct quicklist *q,
	unsigned long min_pages, long max_free)
{
	long pages_to_free;

	pages_to_free = q->nr_pages - max_pages(min_pages);

	return min(pages_to_free, max_free);
}