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
struct rmap_walk_control {void* arg; int /*<<< orphan*/  invalid_vma; int /*<<< orphan*/  rmap_one; } ;
struct page {int dummy; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  invalid_mkclean_vma ; 
 int /*<<< orphan*/  page_mapped (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  page_mkclean_one ; 
 int /*<<< orphan*/  rmap_walk (struct page*,struct rmap_walk_control*) ; 

int page_mkclean(struct page *page)
{
	int cleaned = 0;
	struct address_space *mapping;
	struct rmap_walk_control rwc = {
		.arg = (void *)&cleaned,
		.rmap_one = page_mkclean_one,
		.invalid_vma = invalid_mkclean_vma,
	};

	BUG_ON(!PageLocked(page));

	if (!page_mapped(page))
		return 0;

	mapping = page_mapping(page);
	if (!mapping)
		return 0;

	rmap_walk(page, &rwc);

	return cleaned;
}