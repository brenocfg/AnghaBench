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
typedef  int /*<<< orphan*/  kvm_pfn_t ;

/* Variables and functions */
 unsigned int FOLL_HWPOISON ; 
 unsigned int FOLL_NOWAIT ; 
 unsigned int FOLL_WRITE ; 
 int __get_user_pages_fast (unsigned long,int,int,struct page**) ; 
 int get_user_pages_unlocked (unsigned long,int,struct page**,unsigned int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int hva_to_pfn_slow(unsigned long addr, bool *async, bool write_fault,
			   bool *writable, kvm_pfn_t *pfn)
{
	unsigned int flags = FOLL_HWPOISON;
	struct page *page;
	int npages = 0;

	might_sleep();

	if (writable)
		*writable = write_fault;

	if (write_fault)
		flags |= FOLL_WRITE;
	if (async)
		flags |= FOLL_NOWAIT;

	npages = get_user_pages_unlocked(addr, 1, &page, flags);
	if (npages != 1)
		return npages;

	/* map read fault as writable if possible */
	if (unlikely(!write_fault) && writable) {
		struct page *wpage;

		if (__get_user_pages_fast(addr, 1, 1, &wpage) == 1) {
			*writable = true;
			put_page(page);
			page = wpage;
		}
	}
	*pfn = page_to_pfn(page);
	return npages;
}