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
struct TYPE_5__ {int /*<<< orphan*/  hwndSelf; scalar_t__ defaultFont; int /*<<< orphan*/  edit; scalar_t__ hwndEdit; scalar_t__ hwndCombo; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ COMBOEX_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  COMBOEX_ComboWndProc ; 
 int /*<<< orphan*/  COMBOEX_EditWndProc ; 
 int /*<<< orphan*/  COMBOEX_FreeText (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  COMBOEX_ResetContent (TYPE_1__*) ; 
 int /*<<< orphan*/  COMBO_SUBCLASSID ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  EDIT_SUBCLASSID ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowSubclass (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT COMBOEX_Destroy (COMBOEX_INFO *infoPtr)
{
    if (infoPtr->hwndCombo)
        SetWindowSubclass(infoPtr->hwndCombo, COMBOEX_ComboWndProc, COMBO_SUBCLASSID, 0);

    if (infoPtr->hwndEdit)
        SetWindowSubclass(infoPtr->hwndEdit, COMBOEX_EditWndProc, EDIT_SUBCLASSID, 0);

    COMBOEX_FreeText (&infoPtr->edit);
    COMBOEX_ResetContent (infoPtr);

    if (infoPtr->defaultFont)
	DeleteObject (infoPtr->defaultFont);

    SetWindowLongPtrW (infoPtr->hwndSelf, 0, 0);

    /* free comboex info data */
    Free (infoPtr);

    return 0;
}