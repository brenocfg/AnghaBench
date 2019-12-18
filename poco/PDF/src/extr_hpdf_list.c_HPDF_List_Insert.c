#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; void** obj; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  TYPE_1__* HPDF_List ;
typedef  int HPDF_INT ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_ITEM_NOT_FOUND ; 
 int /*<<< orphan*/  HPDF_List_Add (TYPE_1__*,void*) ; 
 int HPDF_List_Find (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_STATUS
HPDF_List_Insert  (HPDF_List  list,
                   void       *target,
                   void       *item)
{
    HPDF_INT target_idx = HPDF_List_Find (list, target);
    void      *last_item = list->obj[list->count - 1];
    HPDF_INT i;

    HPDF_PTRACE((" HPDF_List_Insert\n"));

    if (target_idx < 0)
        return HPDF_ITEM_NOT_FOUND;

    /* move the item of the list to behind one by one. */
    for (i = list->count - 2; i >= target_idx; i--)
        list->obj[i + 1] = list->obj[i];

    list->obj[target_idx] = item;

    return HPDF_List_Add (list, last_item);
}