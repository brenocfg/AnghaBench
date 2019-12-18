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
struct page {scalar_t__ units; void* freelist; } ;
typedef  int slobidx_t ;
typedef  void slob_t ;

/* Variables and functions */
 int ALIGN (unsigned long,int) ; 
 int SLOB_UNITS (size_t) ; 
 int /*<<< orphan*/  clear_slob_page_free (struct page*) ; 
 int /*<<< orphan*/  set_slob (void*,int,void*) ; 
 scalar_t__ slob_last (void*) ; 
 void* slob_next (void*) ; 
 int slob_units (void*) ; 

__attribute__((used)) static void *slob_page_alloc(struct page *sp, size_t size, int align,
			      int align_offset, bool *page_removed_from_list)
{
	slob_t *prev, *cur, *aligned = NULL;
	int delta = 0, units = SLOB_UNITS(size);

	*page_removed_from_list = false;
	for (prev = NULL, cur = sp->freelist; ; prev = cur, cur = slob_next(cur)) {
		slobidx_t avail = slob_units(cur);

		/*
		 * 'aligned' will hold the address of the slob block so that the
		 * address 'aligned'+'align_offset' is aligned according to the
		 * 'align' parameter. This is for kmalloc() which prepends the
		 * allocated block with its size, so that the block itself is
		 * aligned when needed.
		 */
		if (align) {
			aligned = (slob_t *)
				(ALIGN((unsigned long)cur + align_offset, align)
				 - align_offset);
			delta = aligned - cur;
		}
		if (avail >= units + delta) { /* room enough? */
			slob_t *next;

			if (delta) { /* need to fragment head to align? */
				next = slob_next(cur);
				set_slob(aligned, avail - delta, next);
				set_slob(cur, delta, aligned);
				prev = cur;
				cur = aligned;
				avail = slob_units(cur);
			}

			next = slob_next(cur);
			if (avail == units) { /* exact fit? unlink. */
				if (prev)
					set_slob(prev, slob_units(prev), next);
				else
					sp->freelist = next;
			} else { /* fragment */
				if (prev)
					set_slob(prev, slob_units(prev), cur + units);
				else
					sp->freelist = cur + units;
				set_slob(cur + units, avail - units, next);
			}

			sp->units -= units;
			if (!sp->units) {
				clear_slob_page_free(sp);
				*page_removed_from_list = true;
			}
			return cur;
		}
		if (slob_last(cur))
			return NULL;
	}
}