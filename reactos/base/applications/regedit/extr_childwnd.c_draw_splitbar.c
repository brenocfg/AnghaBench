#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int left; int right; scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ CreateBitmap (int,int,int,int,int const*) ; 
 scalar_t__ CreatePatternBrush (scalar_t__) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATINVERT ; 
 int /*<<< orphan*/  PatBlt (int /*<<< orphan*/ ,int,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SPLIT_WIDTH ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SizingBrush ; 
 scalar_t__ SizingPattern ; 

__attribute__((used)) static void draw_splitbar(HWND hWnd, int x)
{
    RECT rt;
    HGDIOBJ OldObj;
    HDC hdc = GetDC(hWnd);

    if(!SizingPattern)
    {
        const DWORD Pattern[4] = {0x5555AAAA, 0x5555AAAA, 0x5555AAAA, 0x5555AAAA};
        SizingPattern = CreateBitmap(8, 8, 1, 1, Pattern);
    }
    if(!SizingBrush)
    {
        SizingBrush = CreatePatternBrush(SizingPattern);
    }
    GetClientRect(hWnd, &rt);
    rt.left = x - SPLIT_WIDTH/2;
    rt.right = x + SPLIT_WIDTH/2+1;
    OldObj = SelectObject(hdc, SizingBrush);
    PatBlt(hdc, rt.left, rt.top, rt.right - rt.left, rt.bottom - rt.top, PATINVERT);
    SelectObject(hdc, OldObj);
    ReleaseDC(hWnd, hdc);
}