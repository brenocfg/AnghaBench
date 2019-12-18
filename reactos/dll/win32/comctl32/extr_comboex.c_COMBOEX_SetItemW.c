#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_15__ {int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; scalar_t__ pszText; } ;
struct TYPE_14__ {int iItem; int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; scalar_t__ pszText; } ;
struct TYPE_13__ {int nb_items; int /*<<< orphan*/  hwndCombo; int /*<<< orphan*/  hwndEdit; } ;
typedef  int INT_PTR ;
typedef  int INT ;
typedef  TYPE_1__ COMBOEX_INFO ;
typedef  TYPE_2__ COMBOBOXEXITEMW ;
typedef  TYPE_3__ CBE_ITEMDATA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ Alloc (int) ; 
 int CBEIF_IMAGE ; 
 int CBEIF_INDENT ; 
 int CBEIF_LPARAM ; 
 int CBEIF_OVERLAY ; 
 int CBEIF_SELECTEDIMAGE ; 
 int CBEIF_TEXT ; 
 int /*<<< orphan*/  COMBOEX_DumpInput (TYPE_2__ const*) ; 
 int /*<<< orphan*/  COMBOEX_DumpItem (TYPE_3__*) ; 
 TYPE_3__* COMBOEX_FindItem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  COMBOEX_FreeText (TYPE_3__*) ; 
 int /*<<< orphan*/  COMBOEX_SetEditText (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ LPSTR_TEXTCALLBACKW ; 
 int RDW_ERASE ; 
 int RDW_INVALIDATE ; 
 int /*<<< orphan*/  RedrawWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  comboex ; 
 scalar_t__ is_textW (scalar_t__) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__,scalar_t__) ; 
 int strlenW (scalar_t__) ; 

__attribute__((used)) static BOOL COMBOEX_SetItemW (COMBOEX_INFO *infoPtr, const COMBOBOXEXITEMW *cit)
{
    INT_PTR index = cit->iItem;
    CBE_ITEMDATA *item;

    if (TRACE_ON(comboex)) COMBOEX_DumpInput (cit);

    /* if item number requested does not exist then return failure */
    if ((index >= infoPtr->nb_items) || (index < -1)) return FALSE;

    /* if the item is the edit control and there is no edit control, skip */
    if ((index == -1) && !infoPtr->hwndEdit) return FALSE;

    if (!(item = COMBOEX_FindItem(infoPtr, index))) return FALSE;

    /* add/change stuff to the internal item structure */
    item->mask |= cit->mask;
    if (cit->mask & CBEIF_TEXT) {
	INT len = 0;

	COMBOEX_FreeText(item);
        if (is_textW(cit->pszText)) len = strlenW(cit->pszText);
	if (len > 0) {
            item->pszText = Alloc ((len + 1)*sizeof(WCHAR));
	    if (!item->pszText) return FALSE;
	    strcpyW(item->pszText, cit->pszText);
	} else if (cit->pszText == LPSTR_TEXTCALLBACKW)
	    item->pszText = LPSTR_TEXTCALLBACKW;
        item->cchTextMax = cit->cchTextMax;
    }
    if (cit->mask & CBEIF_IMAGE)
        item->iImage = cit->iImage;
    if (cit->mask & CBEIF_SELECTEDIMAGE)
        item->iSelectedImage = cit->iSelectedImage;
    if (cit->mask & CBEIF_OVERLAY)
        item->iOverlay = cit->iOverlay;
    if (cit->mask & CBEIF_INDENT)
        item->iIndent = cit->iIndent;
    if (cit->mask & CBEIF_LPARAM)
        item->lParam = cit->lParam;

    if (TRACE_ON(comboex)) COMBOEX_DumpItem (item);

    /* if original request was to update edit control, do some fast foot work */
    if (cit->iItem == -1 && cit->mask & CBEIF_TEXT) {
	COMBOEX_SetEditText (infoPtr, item);
	RedrawWindow (infoPtr->hwndCombo, 0, 0, RDW_ERASE | RDW_INVALIDATE);
    }
    return TRUE;
}