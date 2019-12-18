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

/* Variables and functions */
 int /*<<< orphan*/  THP_COLLAPSE_ALLOC ; 
 int /*<<< orphan*/  THP_COLLAPSE_ALLOC_FAILED ; 
 struct page* alloc_khugepaged_hugepage () ; 
 int /*<<< orphan*/  count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  khugepaged_alloc_sleep () ; 
 int /*<<< orphan*/  khugepaged_enabled () ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct page *khugepaged_alloc_hugepage(bool *wait)
{
	struct page *hpage;

	do {
		hpage = alloc_khugepaged_hugepage();
		if (!hpage) {
			count_vm_event(THP_COLLAPSE_ALLOC_FAILED);
			if (!*wait)
				return NULL;

			*wait = false;
			khugepaged_alloc_sleep();
		} else
			count_vm_event(THP_COLLAPSE_ALLOC);
	} while (unlikely(!hpage) && likely(khugepaged_enabled()));

	return hpage;
}