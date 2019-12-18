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
struct page {int dummy; } ;
struct gup_benchmark {int size; int nr_pages_per_call; unsigned long addr; int flags; void* put_delta_usec; void* get_delta_usec; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FOLL_LONGTERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  GUP_BENCHMARK 130 
#define  GUP_FAST_BENCHMARK 129 
#define  GUP_LONGTERM_BENCHMARK 128 
 int PAGE_SIZE ; 
 int ULONG_MAX ; 
 int get_user_pages (unsigned long,int,int,struct page**,int /*<<< orphan*/ *) ; 
 int get_user_pages_fast (unsigned long,int,int,struct page**) ; 
 int /*<<< orphan*/  ktime_get () ; 
 void* ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct page** kvcalloc (unsigned long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct page**) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int __gup_benchmark_ioctl(unsigned int cmd,
		struct gup_benchmark *gup)
{
	ktime_t start_time, end_time;
	unsigned long i, nr_pages, addr, next;
	int nr;
	struct page **pages;

	if (gup->size > ULONG_MAX)
		return -EINVAL;

	nr_pages = gup->size / PAGE_SIZE;
	pages = kvcalloc(nr_pages, sizeof(void *), GFP_KERNEL);
	if (!pages)
		return -ENOMEM;

	i = 0;
	nr = gup->nr_pages_per_call;
	start_time = ktime_get();
	for (addr = gup->addr; addr < gup->addr + gup->size; addr = next) {
		if (nr != gup->nr_pages_per_call)
			break;

		next = addr + nr * PAGE_SIZE;
		if (next > gup->addr + gup->size) {
			next = gup->addr + gup->size;
			nr = (next - addr) / PAGE_SIZE;
		}

		switch (cmd) {
		case GUP_FAST_BENCHMARK:
			nr = get_user_pages_fast(addr, nr, gup->flags & 1,
						 pages + i);
			break;
		case GUP_LONGTERM_BENCHMARK:
			nr = get_user_pages(addr, nr,
					    (gup->flags & 1) | FOLL_LONGTERM,
					    pages + i, NULL);
			break;
		case GUP_BENCHMARK:
			nr = get_user_pages(addr, nr, gup->flags & 1, pages + i,
					    NULL);
			break;
		default:
			return -1;
		}

		if (nr <= 0)
			break;
		i += nr;
	}
	end_time = ktime_get();

	gup->get_delta_usec = ktime_us_delta(end_time, start_time);
	gup->size = addr - gup->addr;

	start_time = ktime_get();
	for (i = 0; i < nr_pages; i++) {
		if (!pages[i])
			break;
		put_page(pages[i]);
	}
	end_time = ktime_get();
	gup->put_delta_usec = ktime_us_delta(end_time, start_time);

	kvfree(pages);
	return 0;
}