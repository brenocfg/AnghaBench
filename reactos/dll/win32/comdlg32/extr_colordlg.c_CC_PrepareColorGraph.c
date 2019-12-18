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
struct TYPE_7__ {int /*<<< orphan*/  hdcMem; int /*<<< orphan*/  hbmMem; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_6__ {int right; int bottom; int left; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  TYPE_2__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  CC_HSLtoRGB (int,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COLOR_GRAPH ; 
 scalar_t__ IDC_WAIT ; 
 int /*<<< orphan*/  LoadCursorW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int XSTEPS ; 
 int YSTEPS ; 

__attribute__((used)) static void CC_PrepareColorGraph(CCPRIV *infoPtr)
{
 int sdif, hdif, xdif, ydif, hue, sat;
 HWND hwnd = GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_GRAPH);
 HBRUSH hbrush;
 HDC hdc ;
 RECT rect, client;
 HCURSOR hcursor = SetCursor( LoadCursorW(0, (LPCWSTR)IDC_WAIT) );

 GetClientRect(hwnd, &client);
 hdc = GetDC(hwnd);
 infoPtr->hdcMem = CreateCompatibleDC(hdc);
 infoPtr->hbmMem = CreateCompatibleBitmap(hdc, client.right, client.bottom);
 SelectObject(infoPtr->hdcMem, infoPtr->hbmMem);

 xdif = client.right / XSTEPS;
 ydif = client.bottom / YSTEPS+1;
 hdif = 239 / XSTEPS;
 sdif = 240 / YSTEPS;
 for (rect.left = hue = 0; hue < 239 + hdif; hue += hdif)
 {
  rect.right = rect.left + xdif;
  rect.bottom = client.bottom;
  for(sat = 0; sat < 240 + sdif; sat += sdif)
  {
   rect.top = rect.bottom - ydif;
   hbrush = CreateSolidBrush(CC_HSLtoRGB(hue, sat, 120));
   FillRect(infoPtr->hdcMem, &rect, hbrush);
   DeleteObject(hbrush);
   rect.bottom = rect.top;
  }
  rect.left = rect.right;
 }
 ReleaseDC(hwnd, hdc);
 SetCursor(hcursor);
}