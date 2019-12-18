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
struct page {int /*<<< orphan*/  slab_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ClearPageSlobFree (struct page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_slob_page_free(struct page *sp)
{
	list_del(&sp->slab_list);
	__ClearPageSlobFree(sp);
}