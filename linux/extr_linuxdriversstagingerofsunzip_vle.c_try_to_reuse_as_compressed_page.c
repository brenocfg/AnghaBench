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
struct z_erofs_vle_work_builder {int /*<<< orphan*/  compressed_pages; scalar_t__ compressed_deficit; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cmpxchg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct page*) ; 

__attribute__((used)) static inline bool try_to_reuse_as_compressed_page(
	struct z_erofs_vle_work_builder *b,
	struct page *page)
{
	while (b->compressed_deficit) {
		--b->compressed_deficit;
		if (NULL == cmpxchg(b->compressed_pages++, NULL, page))
			return true;
	}

	return false;
}