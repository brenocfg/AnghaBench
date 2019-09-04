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
struct quicklist {unsigned long nr_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_page (unsigned long) ; 
 struct quicklist* get_cpu_var (int /*<<< orphan*/ ) ; 
 long min_pages_to_free (struct quicklist*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicklist ; 
 void* quicklist_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void quicklist_trim(int nr, void (*dtor)(void *),
	unsigned long min_pages, unsigned long max_free)
{
	long pages_to_free;
	struct quicklist *q;

	q = &get_cpu_var(quicklist)[nr];
	if (q->nr_pages > min_pages) {
		pages_to_free = min_pages_to_free(q, min_pages, max_free);

		while (pages_to_free > 0) {
			/*
			 * We pass a gfp_t of 0 to quicklist_alloc here
			 * because we will never call into the page allocator.
			 */
			void *p = quicklist_alloc(nr, 0, NULL);

			if (dtor)
				dtor(p);
			free_page((unsigned long)p);
			pages_to_free--;
		}
	}
	put_cpu_var(quicklist);
}