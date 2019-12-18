#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int iItem; } ;
struct TYPE_7__ {int nb_items; int /*<<< orphan*/  hwndEdit; } ;
typedef  int INT_PTR ;
typedef  TYPE_1__ COMBOEX_INFO ;
typedef  TYPE_2__ COMBOBOXEXITEMW ;
typedef  int /*<<< orphan*/  CBE_ITEMDATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  COMBOEX_CopyItem (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * COMBOEX_FindItem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL COMBOEX_GetItemW (COMBOEX_INFO *infoPtr, COMBOBOXEXITEMW *cit)
{
    INT_PTR index = cit->iItem;
    CBE_ITEMDATA *item;

    TRACE("\n");

    /* if item number requested does not exist then return failure */
    if ((index >= infoPtr->nb_items) || (index < -1)) return FALSE;

    /* if the item is the edit control and there is no edit control, skip */
    if ((index == -1) && !infoPtr->hwndEdit) return FALSE;

    if (!(item = COMBOEX_FindItem(infoPtr, index))) return FALSE;

    COMBOEX_CopyItem (item, cit);

    return TRUE;
}