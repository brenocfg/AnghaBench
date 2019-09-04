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
struct tracing_map_array {int entry_size_shift; int entries_per_page; unsigned int n_pages; int entry_shift; int entry_mask; void** pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 void* fls (unsigned int) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 void** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct tracing_map_array* kzalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int roundup_pow_of_two (unsigned int) ; 
 int /*<<< orphan*/  tracing_map_array_free (struct tracing_map_array*) ; 

struct tracing_map_array *tracing_map_array_alloc(unsigned int n_elts,
						  unsigned int entry_size)
{
	struct tracing_map_array *a;
	unsigned int i;

	a = kzalloc(sizeof(*a), GFP_KERNEL);
	if (!a)
		return NULL;

	a->entry_size_shift = fls(roundup_pow_of_two(entry_size) - 1);
	a->entries_per_page = PAGE_SIZE / (1 << a->entry_size_shift);
	a->n_pages = n_elts / a->entries_per_page;
	if (!a->n_pages)
		a->n_pages = 1;
	a->entry_shift = fls(a->entries_per_page) - 1;
	a->entry_mask = (1 << a->entry_shift) - 1;

	a->pages = kcalloc(a->n_pages, sizeof(void *), GFP_KERNEL);
	if (!a->pages)
		goto free;

	for (i = 0; i < a->n_pages; i++) {
		a->pages[i] = (void *)get_zeroed_page(GFP_KERNEL);
		if (!a->pages[i])
			goto free;
	}
 out:
	return a;
 free:
	tracing_map_array_free(a);
	a = NULL;

	goto out;
}