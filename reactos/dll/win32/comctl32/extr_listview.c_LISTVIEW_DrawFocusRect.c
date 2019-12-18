#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ left; scalar_t__ right; } ;
struct TYPE_4__ {TYPE_3__ rcFocus; } ;
typedef  TYPE_1__ LISTVIEW_INFO ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DrawFocusRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RGB (int,int,int) ; 
 int /*<<< orphan*/  SetBkColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline BOOL LISTVIEW_DrawFocusRect(const LISTVIEW_INFO *infoPtr, HDC hdc)
{
#ifdef __REACTOS__
    BOOL Ret = FALSE;

    if (infoPtr->rcFocus.left < infoPtr->rcFocus.right)
    {
        DWORD dwOldBkColor, dwOldTextColor;

        dwOldBkColor = SetBkColor(hdc, RGB(255, 255, 255));
        dwOldTextColor = SetBkColor(hdc, RGB(0, 0, 0));
        Ret = DrawFocusRect(hdc, &infoPtr->rcFocus);
        SetBkColor(hdc, dwOldBkColor);
        SetBkColor(hdc, dwOldTextColor);
    }
    return Ret;
#else
    return (infoPtr->rcFocus.left < infoPtr->rcFocus.right) ?
            DrawFocusRect(hdc, &infoPtr->rcFocus) : FALSE;
#endif
}