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
 int /*<<< orphan*/  __free_page (struct page*) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 

__attribute__((used)) static void nfs4_free_pages(struct page **pages, size_t size)
{
	int i;

	if (!pages)
		return;

	for (i = 0; i < size; i++) {
		if (!pages[i])
			break;
		__free_page(pages[i]);
	}
	kfree(pages);
}