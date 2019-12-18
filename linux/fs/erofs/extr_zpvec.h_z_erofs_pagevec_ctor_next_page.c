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
struct z_erofs_pagevec_ctor {unsigned int nr; int /*<<< orphan*/ * pages; struct page* next; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  erofs_vtptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 unsigned int const Z_EROFS_PAGE_TYPE_EXCLUSIVE ; 
 struct page* tagptr_unfold_ptr (int /*<<< orphan*/  const) ; 
 unsigned int tagptr_unfold_tags (int /*<<< orphan*/  const) ; 

__attribute__((used)) static inline struct page *
z_erofs_pagevec_ctor_next_page(struct z_erofs_pagevec_ctor *ctor,
			       unsigned int nr)
{
	unsigned int index;

	/* keep away from occupied pages */
	if (ctor->next)
		return ctor->next;

	for (index = 0; index < nr; ++index) {
		const erofs_vtptr_t t = ctor->pages[index];
		const unsigned int tags = tagptr_unfold_tags(t);

		if (tags == Z_EROFS_PAGE_TYPE_EXCLUSIVE)
			return tagptr_unfold_ptr(t);
	}
	DBG_BUGON(nr >= ctor->nr);
	return NULL;
}