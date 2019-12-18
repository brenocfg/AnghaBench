#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pszText; } ;
struct TYPE_8__ {int /*<<< orphan*/  hwndCombo; int /*<<< orphan*/  selected; } ;
typedef  int /*<<< orphan*/  INT_PTR ;
typedef  scalar_t__ INT ;
typedef  TYPE_1__ COMBOEX_INFO ;
typedef  TYPE_2__ CBE_ITEMDATA ;

/* Variables and functions */
 int /*<<< orphan*/  CB_SETCURSEL ; 
 TYPE_2__* COMBOEX_FindItem (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMBOEX_SetEditText (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_txt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT COMBOEX_SetCursel (COMBOEX_INFO *infoPtr, INT_PTR index)
{
    CBE_ITEMDATA *item;
    INT sel;

    if (!(item = COMBOEX_FindItem(infoPtr, index)))
	return SendMessageW (infoPtr->hwndCombo, CB_SETCURSEL, index, 0);

    TRACE("selecting item %ld text=%s\n", index, debugstr_txt(item->pszText));
    infoPtr->selected = index;

    sel = (INT)SendMessageW (infoPtr->hwndCombo, CB_SETCURSEL, index, 0);
    COMBOEX_SetEditText (infoPtr, item);
    return sel;
}