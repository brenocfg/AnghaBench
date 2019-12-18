#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nmia ;
struct TYPE_15__ {int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_14__ {int /*<<< orphan*/  iItem; int /*<<< orphan*/  pt; int /*<<< orphan*/  iSubItem; } ;
struct TYPE_13__ {int /*<<< orphan*/  lParam; scalar_t__ iSubItem; int /*<<< orphan*/  iItem; int /*<<< orphan*/  mask; } ;
struct TYPE_12__ {int /*<<< orphan*/  lParam; int /*<<< orphan*/  ptAction; int /*<<< orphan*/  iSubItem; int /*<<< orphan*/  iItem; } ;
typedef  TYPE_1__ NMITEMACTIVATE ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  TYPE_2__ LVITEMW ;
typedef  TYPE_3__ LVHITTESTINFO ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_4__ LISTVIEW_INFO ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ IsWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ LISTVIEW_GetItemT (TYPE_4__ const*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  LVIF_PARAM ; 
 scalar_t__ NM_RCLICK ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  debuglvhittestinfo (TYPE_3__ const*) ; 
 int /*<<< orphan*/  notify_hdr (TYPE_4__ const*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL notify_click(const LISTVIEW_INFO *infoPtr, INT code, const LVHITTESTINFO *lvht)
{
    NMITEMACTIVATE nmia;
    LVITEMW item;
    HWND hwnd = infoPtr->hwndSelf;
    LRESULT ret;

    TRACE("code=%d, lvht=%s\n", code, debuglvhittestinfo(lvht)); 
    ZeroMemory(&nmia, sizeof(nmia));
    nmia.iItem = lvht->iItem;
    nmia.iSubItem = lvht->iSubItem;
    nmia.ptAction = lvht->pt;
    item.mask = LVIF_PARAM;
    item.iItem = lvht->iItem;
    item.iSubItem = 0;
    if (LISTVIEW_GetItemT(infoPtr, &item, TRUE)) nmia.lParam = item.lParam;
    ret = notify_hdr(infoPtr, code, (NMHDR*)&nmia);
    return IsWindow(hwnd) && (code == NM_RCLICK ? !ret : TRUE);
}