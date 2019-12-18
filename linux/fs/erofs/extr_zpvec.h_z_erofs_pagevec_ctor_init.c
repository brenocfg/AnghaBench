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
struct z_erofs_pagevec_ctor {unsigned int nr; unsigned int index; int /*<<< orphan*/ * next; int /*<<< orphan*/ * pages; int /*<<< orphan*/  curr; } ;
typedef  int /*<<< orphan*/  erofs_vtptr_t ;

/* Variables and functions */
 int /*<<< orphan*/ * z_erofs_pagevec_ctor_next_page (struct z_erofs_pagevec_ctor*,unsigned int) ; 
 int /*<<< orphan*/  z_erofs_pagevec_ctor_pagedown (struct z_erofs_pagevec_ctor*,int) ; 

__attribute__((used)) static inline void z_erofs_pagevec_ctor_init(struct z_erofs_pagevec_ctor *ctor,
					     unsigned int nr,
					     erofs_vtptr_t *pages,
					     unsigned int i)
{
	ctor->nr = nr;
	ctor->curr = ctor->next = NULL;
	ctor->pages = pages;

	if (i >= nr) {
		i -= nr;
		z_erofs_pagevec_ctor_pagedown(ctor, false);
		while (i > ctor->nr) {
			i -= ctor->nr;
			z_erofs_pagevec_ctor_pagedown(ctor, false);
		}
	}
	ctor->next = z_erofs_pagevec_ctor_next_page(ctor, i);
	ctor->index = i;
}