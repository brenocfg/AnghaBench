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
struct TYPE_6__ {int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_5__ {scalar_t__ bDown; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  scalar_t__ HTHEME ;
typedef  TYPE_1__ HEADER_ITEM ;
typedef  TYPE_2__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawThemeBackground (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetBkColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetThemeBackgroundContentRect (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ GetWindowTheme (int /*<<< orphan*/ ) ; 
 int HIS_HOT ; 
 int HIS_NORMAL ; 
 int HIS_PRESSED ; 
 int /*<<< orphan*/  HP_HEADERITEM ; 

__attribute__((used)) static void
HEADER_FillItemFrame(HEADER_INFO *infoPtr, HDC hdc, RECT *r, const HEADER_ITEM *item, BOOL hottrack)
{
    HTHEME theme = GetWindowTheme (infoPtr->hwndSelf);

    if (theme) {
        int state = (item->bDown) ? HIS_PRESSED : (hottrack ? HIS_HOT : HIS_NORMAL);
        DrawThemeBackground (theme, hdc, HP_HEADERITEM, state, r, NULL);
        GetThemeBackgroundContentRect (theme, hdc, HP_HEADERITEM, state, r, r);
    }
    else
    {
        HBRUSH hbr = CreateSolidBrush(GetBkColor(hdc));
        FillRect(hdc, r, hbr);
        DeleteObject(hbr);
    }
}