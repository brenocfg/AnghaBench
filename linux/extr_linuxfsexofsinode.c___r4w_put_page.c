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
struct page_collect {struct page* that_locked_page; } ;
struct page {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG2 (char*,int) ; 
 struct page* ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static void __r4w_put_page(void *priv, struct page *page)
{
	struct page_collect *pcol = priv;

	if ((pcol->that_locked_page != page) && (ZERO_PAGE(0) != page)) {
		EXOFS_DBGMSG2("index=0x%lx\n", page->index);
		put_page(page);
		return;
	}
	EXOFS_DBGMSG2("that_locked_page index=0x%lx\n",
		     ZERO_PAGE(0) == page ? -1 : page->index);
}