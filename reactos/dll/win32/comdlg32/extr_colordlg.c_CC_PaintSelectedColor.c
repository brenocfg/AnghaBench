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
struct TYPE_5__ {TYPE_1__* lpcc; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_4__ {int /*<<< orphan*/  rgbResult; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  TYPE_2__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  BDR_SUNKENOUTER ; 
 int /*<<< orphan*/  BF_RECT ; 
 scalar_t__ CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COLOR_GRAPH ; 
 int /*<<< orphan*/  IDC_COLOR_RESULT ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CC_PaintSelectedColor(const CCPRIV *infoPtr)
{
 if (IsWindowVisible( GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_GRAPH) ))   /* if full size */
 {
  RECT rect;
  HDC  hdc;
  HBRUSH hBrush;
  HWND hwnd = GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_RESULT);

  hdc = GetDC(hwnd);
  GetClientRect(hwnd, &rect) ;
  hBrush = CreateSolidBrush(infoPtr->lpcc->rgbResult);
  if (hBrush)
  {
   FillRect(hdc, &rect, hBrush);
   DrawEdge(hdc, &rect, BDR_SUNKENOUTER, BF_RECT);
   DeleteObject(hBrush);
  }
  ReleaseDC(hwnd, hdc);
 }
}