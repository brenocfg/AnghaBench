#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer {int aux_nr_pages; int aux_overwrite; long aux_watermark; int /*<<< orphan*/  aux_pgoff; int /*<<< orphan*/  aux_refcount; int /*<<< orphan*/  aux_priv; int /*<<< orphan*/ * aux_pages; int /*<<< orphan*/  free_aux; } ;
struct perf_event {int cpu; TYPE_1__* pmu; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_2__ {int capabilities; int /*<<< orphan*/  (* setup_aux ) (struct perf_event*,int /*<<< orphan*/ *,int,int) ;int /*<<< orphan*/  free_aux; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int PERF_PMU_CAP_AUX_NO_SG ; 
 int RING_BUFFER_WRITABLE ; 
 int /*<<< orphan*/  __rb_free_aux (struct ring_buffer*) ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  has_aux (struct perf_event*) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/ * kcalloc_node (int,int,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int page_private (struct page*) ; 
 struct page* rb_alloc_aux_page (int,int) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct perf_event*,int /*<<< orphan*/ *,int,int) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

int rb_alloc_aux(struct ring_buffer *rb, struct perf_event *event,
		 pgoff_t pgoff, int nr_pages, long watermark, int flags)
{
	bool overwrite = !(flags & RING_BUFFER_WRITABLE);
	int node = (event->cpu == -1) ? -1 : cpu_to_node(event->cpu);
	int ret = -ENOMEM, max_order;

	if (!has_aux(event))
		return -EOPNOTSUPP;

	/*
	 * We need to start with the max_order that fits in nr_pages,
	 * not the other way around, hence ilog2() and not get_order.
	 */
	max_order = ilog2(nr_pages);

	/*
	 * PMU requests more than one contiguous chunks of memory
	 * for SW double buffering
	 */
	if (!overwrite) {
		if (!max_order)
			return -EINVAL;

		max_order--;
	}

	rb->aux_pages = kcalloc_node(nr_pages, sizeof(void *), GFP_KERNEL,
				     node);
	if (!rb->aux_pages)
		return -ENOMEM;

	rb->free_aux = event->pmu->free_aux;
	for (rb->aux_nr_pages = 0; rb->aux_nr_pages < nr_pages;) {
		struct page *page;
		int last, order;

		order = min(max_order, ilog2(nr_pages - rb->aux_nr_pages));
		page = rb_alloc_aux_page(node, order);
		if (!page)
			goto out;

		for (last = rb->aux_nr_pages + (1 << page_private(page));
		     last > rb->aux_nr_pages; rb->aux_nr_pages++)
			rb->aux_pages[rb->aux_nr_pages] = page_address(page++);
	}

	/*
	 * In overwrite mode, PMUs that don't support SG may not handle more
	 * than one contiguous allocation, since they rely on PMI to do double
	 * buffering. In this case, the entire buffer has to be one contiguous
	 * chunk.
	 */
	if ((event->pmu->capabilities & PERF_PMU_CAP_AUX_NO_SG) &&
	    overwrite) {
		struct page *page = virt_to_page(rb->aux_pages[0]);

		if (page_private(page) != max_order)
			goto out;
	}

	rb->aux_priv = event->pmu->setup_aux(event, rb->aux_pages, nr_pages,
					     overwrite);
	if (!rb->aux_priv)
		goto out;

	ret = 0;

	/*
	 * aux_pages (and pmu driver's private data, aux_priv) will be
	 * referenced in both producer's and consumer's contexts, thus
	 * we keep a refcount here to make sure either of the two can
	 * reference them safely.
	 */
	refcount_set(&rb->aux_refcount, 1);

	rb->aux_overwrite = overwrite;
	rb->aux_watermark = watermark;

	if (!rb->aux_watermark && !rb->aux_overwrite)
		rb->aux_watermark = nr_pages << (PAGE_SHIFT - 1);

out:
	if (!ret)
		rb->aux_pgoff = pgoff;
	else
		__rb_free_aux(rb);

	return ret;
}