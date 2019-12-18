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
struct z_erofs_pagevec_ctor {scalar_t__ index; scalar_t__ nr; int /*<<< orphan*/ * pages; struct page* next; } ;
struct page {int dummy; } ;
typedef  enum z_erofs_page_type { ____Placeholder_z_erofs_page_type } z_erofs_page_type ;

/* Variables and functions */
 uintptr_t Z_EROFS_PAGE_TYPE_EXCLUSIVE ; 
 int /*<<< orphan*/  __bad_page_type_exclusive () ; 
 int /*<<< orphan*/  erofs_vtptr_t ; 
 int /*<<< orphan*/  tagptr_fold (int /*<<< orphan*/ ,struct page*,int) ; 
 int /*<<< orphan*/  z_erofs_pagevec_ctor_pagedown (struct z_erofs_pagevec_ctor*,int) ; 

__attribute__((used)) static inline bool z_erofs_pagevec_enqueue(struct z_erofs_pagevec_ctor *ctor,
					   struct page *page,
					   enum z_erofs_page_type type,
					   bool *occupied)
{
	*occupied = false;
	if (!ctor->next && type)
		if (ctor->index + 1 == ctor->nr)
			return false;

	if (ctor->index >= ctor->nr)
		z_erofs_pagevec_ctor_pagedown(ctor, false);

	/* exclusive page type must be 0 */
	if (Z_EROFS_PAGE_TYPE_EXCLUSIVE != (uintptr_t)NULL)
		__bad_page_type_exclusive();

	/* should remind that collector->next never equal to 1, 2 */
	if (type == (uintptr_t)ctor->next) {
		ctor->next = page;
		*occupied = true;
	}
	ctor->pages[ctor->index++] = tagptr_fold(erofs_vtptr_t, page, type);
	return true;
}