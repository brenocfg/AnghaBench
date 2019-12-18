#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_19__ {int /*<<< orphan*/  mask; } ;
struct TYPE_18__ {int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; void* pszText; struct TYPE_18__* next; } ;
struct TYPE_17__ {int iItem; int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; int /*<<< orphan*/  cchTextMax; void* pszText; } ;
struct TYPE_16__ {int nb_items; int /*<<< orphan*/  hwndCombo; TYPE_4__* items; } ;
struct TYPE_15__ {TYPE_5__ ceItem; } ;
typedef  TYPE_1__ NMCOMBOBOXEXW ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT_PTR ;
typedef  int INT ;
typedef  TYPE_2__ COMBOEX_INFO ;
typedef  TYPE_3__ COMBOBOXEXITEMW ;
typedef  TYPE_4__ CBE_ITEMDATA ;

/* Variables and functions */
 void* Alloc (int) ; 
 int CBEIF_IMAGE ; 
 int CBEIF_INDENT ; 
 int CBEIF_LPARAM ; 
 int CBEIF_OVERLAY ; 
 int CBEIF_SELECTEDIMAGE ; 
 int CBEIF_TEXT ; 
 int /*<<< orphan*/  CBEN_INSERTITEM ; 
 int /*<<< orphan*/  CB_INSERTSTRING ; 
 int /*<<< orphan*/  COMBOEX_CopyItem (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  COMBOEX_DumpInput (TYPE_3__ const*) ; 
 int /*<<< orphan*/  COMBOEX_DumpItem (TYPE_4__*) ; 
 int /*<<< orphan*/  COMBOEX_NotifyItem (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  Free (TYPE_4__*) ; 
 void* LPSTR_TEXTCALLBACKW ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ TRACE_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comboex ; 
 scalar_t__ is_textW (void*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcpyW (void*,void*) ; 
 int strlenW (void*) ; 

__attribute__((used)) static INT COMBOEX_InsertItemW (COMBOEX_INFO *infoPtr, COMBOBOXEXITEMW const *cit)
{
    INT_PTR index;
    CBE_ITEMDATA *item;
    NMCOMBOBOXEXW nmcit;

    TRACE("\n");

    if (TRACE_ON(comboex)) COMBOEX_DumpInput (cit);

    /* get real index of item to insert */
    index = cit->iItem;
    if (index == -1) index = infoPtr->nb_items;
    if (index > infoPtr->nb_items) return -1;

    /* get zero-filled space and chain it in */
    if(!(item = Alloc (sizeof(*item)))) return -1;

    /* locate position to insert new item in */
    if (index == infoPtr->nb_items) {
        /* fast path for iItem = -1 */
        item->next = infoPtr->items;
	infoPtr->items = item;
    }
    else {
        INT i = infoPtr->nb_items-1;
	CBE_ITEMDATA *moving = infoPtr->items;

	while ((i > index) && moving) {
	    moving = moving->next;
	    i--;
	}
	if (!moving) {
	    ERR("COMBOBOXEX item structures broken. Please report!\n");
	    Free(item);
	    return -1;
	}
	item->next = moving->next;
	moving->next = item;
    }

    /* fill in our hidden item structure */
    item->mask = cit->mask;
    if (item->mask & CBEIF_TEXT) {
	INT len = 0;

        if (is_textW(cit->pszText)) len = strlenW (cit->pszText);
	if (len > 0) {
            item->pszText = Alloc ((len + 1)*sizeof(WCHAR));
	    if (!item->pszText) {
		Free(item);
		return -1;
	    }
	    strcpyW (item->pszText, cit->pszText);
	}
	else if (cit->pszText == LPSTR_TEXTCALLBACKW)
	    item->pszText = LPSTR_TEXTCALLBACKW;
        item->cchTextMax = cit->cchTextMax;
    }
    if (item->mask & CBEIF_IMAGE)
        item->iImage = cit->iImage;
    if (item->mask & CBEIF_SELECTEDIMAGE)
        item->iSelectedImage = cit->iSelectedImage;
    if (item->mask & CBEIF_OVERLAY)
        item->iOverlay = cit->iOverlay;
    if (item->mask & CBEIF_INDENT)
        item->iIndent = cit->iIndent;
    if (item->mask & CBEIF_LPARAM)
        item->lParam = cit->lParam;
    infoPtr->nb_items++;

    if (TRACE_ON(comboex)) COMBOEX_DumpItem (item);

    SendMessageW (infoPtr->hwndCombo, CB_INSERTSTRING, cit->iItem, (LPARAM)item);

    memset (&nmcit.ceItem, 0, sizeof(nmcit.ceItem));
    nmcit.ceItem.mask=~0;
    COMBOEX_CopyItem (item, &nmcit.ceItem);
    COMBOEX_NotifyItem (infoPtr, CBEN_INSERTITEM, &nmcit);

    return index;

}