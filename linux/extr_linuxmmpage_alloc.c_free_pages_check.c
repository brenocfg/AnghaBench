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
 int /*<<< orphan*/  PAGE_FLAGS_CHECK_AT_FREE ; 
 int /*<<< orphan*/  free_pages_check_bad (struct page*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_expected_state (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int free_pages_check(struct page *page)
{
	if (likely(page_expected_state(page, PAGE_FLAGS_CHECK_AT_FREE)))
		return 0;

	/* Something has gone sideways, find it */
	free_pages_check_bad(page);
	return 1;
}