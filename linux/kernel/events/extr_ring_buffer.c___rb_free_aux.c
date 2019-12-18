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
struct ring_buffer {int aux_nr_pages; int /*<<< orphan*/  aux_pages; int /*<<< orphan*/ * aux_priv; int /*<<< orphan*/  (* free_aux ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_atomic () ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_free_aux_page (struct ring_buffer*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __rb_free_aux(struct ring_buffer *rb)
{
	int pg;

	/*
	 * Should never happen, the last reference should be dropped from
	 * perf_mmap_close() path, which first stops aux transactions (which
	 * in turn are the atomic holders of aux_refcount) and then does the
	 * last rb_free_aux().
	 */
	WARN_ON_ONCE(in_atomic());

	if (rb->aux_priv) {
		rb->free_aux(rb->aux_priv);
		rb->free_aux = NULL;
		rb->aux_priv = NULL;
	}

	if (rb->aux_nr_pages) {
		for (pg = 0; pg < rb->aux_nr_pages; pg++)
			rb_free_aux_page(rb, pg);

		kfree(rb->aux_pages);
		rb->aux_nr_pages = 0;
	}
}