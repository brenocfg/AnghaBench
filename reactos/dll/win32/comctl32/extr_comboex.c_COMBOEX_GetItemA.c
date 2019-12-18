#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; scalar_t__* pszText; int /*<<< orphan*/  cchTextMax; int /*<<< orphan*/  iItem; } ;
struct TYPE_5__ {int mask; int /*<<< orphan*/  lParam; int /*<<< orphan*/  iIndent; int /*<<< orphan*/  iOverlay; int /*<<< orphan*/  iSelectedImage; int /*<<< orphan*/  iImage; scalar_t__ pszText; int /*<<< orphan*/  iItem; } ;
typedef  scalar_t__* LPSTR ;
typedef  int /*<<< orphan*/  COMBOEX_INFO ;
typedef  TYPE_1__ COMBOBOXEXITEMW ;
typedef  TYPE_2__ COMBOBOXEXITEMA ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int CBEIF_IMAGE ; 
 int CBEIF_INDENT ; 
 int CBEIF_LPARAM ; 
 int CBEIF_OVERLAY ; 
 int CBEIF_SELECTEDIMAGE ; 
 int CBEIF_TEXT ; 
 int /*<<< orphan*/  COMBOEX_GetItemW (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_textW (scalar_t__) ; 

__attribute__((used)) static BOOL COMBOEX_GetItemA (COMBOEX_INFO *infoPtr, COMBOBOXEXITEMA *cit)
{
    COMBOBOXEXITEMW tmpcit;

    TRACE("\n");

    tmpcit.mask = cit->mask;
    tmpcit.iItem = cit->iItem;
    tmpcit.pszText = 0;
    if(!COMBOEX_GetItemW (infoPtr, &tmpcit)) return FALSE;

    if (cit->mask & CBEIF_TEXT)
    {
        if (is_textW(tmpcit.pszText) && cit->pszText)
            WideCharToMultiByte(CP_ACP, 0, tmpcit.pszText, -1,
                                cit->pszText, cit->cchTextMax, NULL, NULL);
        else if (cit->pszText) cit->pszText[0] = 0;
        else cit->pszText = (LPSTR)tmpcit.pszText;
    }

    if (cit->mask & CBEIF_IMAGE)
        cit->iImage = tmpcit.iImage;
    if (cit->mask & CBEIF_SELECTEDIMAGE)
        cit->iSelectedImage = tmpcit.iSelectedImage;
    if (cit->mask & CBEIF_OVERLAY)
        cit->iOverlay = tmpcit.iOverlay;
    if (cit->mask & CBEIF_INDENT)
        cit->iIndent = tmpcit.iIndent;
    if (cit->mask & CBEIF_LPARAM)
        cit->lParam = tmpcit.lParam;

    return TRUE;
}