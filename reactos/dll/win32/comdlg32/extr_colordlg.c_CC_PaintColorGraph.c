#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hdcMem; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_6__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_2__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  BitBlt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_PrepareColorGraph (TYPE_2__*) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COLOR_GRAPH ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  WARN (char*) ; 

__attribute__((used)) static void CC_PaintColorGraph(CCPRIV *infoPtr)
{
 HWND hwnd = GetDlgItem( infoPtr->hwndSelf, IDC_COLOR_GRAPH );
 HDC  hDC;
 RECT rect;

 if (IsWindowVisible(hwnd))   /* if full size */
 {
  if (!infoPtr->hdcMem)
   CC_PrepareColorGraph(infoPtr);   /* should not be necessary */

  hDC = GetDC(hwnd);
  GetClientRect(hwnd, &rect);
  if (infoPtr->hdcMem)
      BitBlt(hDC, 0, 0, rect.right, rect.bottom, infoPtr->hdcMem, 0, 0, SRCCOPY);
  else
      WARN("choose color: hdcMem is not defined\n");
  ReleaseDC(hwnd, hDC);
 }
}