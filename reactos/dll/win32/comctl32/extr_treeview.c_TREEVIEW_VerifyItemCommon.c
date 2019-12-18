#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ parent; struct TYPE_3__ const* nextSibling; struct TYPE_3__ const* prevSibling; struct TYPE_3__ const* lastChild; struct TYPE_3__ const* firstChild; } ;
typedef  TYPE_1__ TREEVIEW_ITEM ;
typedef  int /*<<< orphan*/  TREEVIEW_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline void TREEVIEW_VerifyItemCommon(TREEVIEW_INFO *infoPtr,
					     const TREEVIEW_ITEM *item)
{
    assert(infoPtr != NULL);
    assert(item != NULL);

    /* both NULL, or both non-null */
    assert((item->firstChild == NULL) == (item->lastChild == NULL));

    assert(item->firstChild != item);
    assert(item->lastChild != item);

    if (item->firstChild)
    {
	assert(item->firstChild->parent == item);
	assert(item->firstChild->prevSibling == NULL);
    }

    if (item->lastChild)
    {
	assert(item->lastChild->parent == item);
	assert(item->lastChild->nextSibling == NULL);
    }

    assert(item->nextSibling != item);
    if (item->nextSibling)
    {
	assert(item->nextSibling->parent == item->parent);
	assert(item->nextSibling->prevSibling == item);
    }

    assert(item->prevSibling != item);
    if (item->prevSibling)
    {
	assert(item->prevSibling->parent == item->parent);
	assert(item->prevSibling->nextSibling == item);
    }
}