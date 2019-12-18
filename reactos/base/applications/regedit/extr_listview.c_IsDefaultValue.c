#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int iItem; scalar_t__ lParam; int /*<<< orphan*/  mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* PLINE_INFO ;
typedef  TYPE_2__ LVITEMW ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LVIF_PARAM ; 
 scalar_t__ ListView_GetItem (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ ,char*) ; 

BOOL IsDefaultValue(HWND hwndLV, int i)
{
    PLINE_INFO lineinfo;
    LVITEMW Item;

    Item.mask = LVIF_PARAM;
    Item.iItem = i;
    if(ListView_GetItem(hwndLV, &Item))
    {
        lineinfo = (PLINE_INFO)Item.lParam;
        return lineinfo && (!lineinfo->name || !wcscmp(lineinfo->name, L""));
    }
    return FALSE;
}