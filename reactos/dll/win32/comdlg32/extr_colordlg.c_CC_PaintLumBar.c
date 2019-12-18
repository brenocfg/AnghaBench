#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s; int /*<<< orphan*/  h; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_7__ {int bottom; int top; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  TYPE_2__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  BDR_SUNKENOUTER ; 
 int /*<<< orphan*/  BF_RECT ; 
 int /*<<< orphan*/  CC_HSLtoRGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DrawEdge (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_COLOR_LUMBAR ; 
 scalar_t__ IsWindowVisible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int YSTEPS ; 
 int max (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void CC_PaintLumBar(const CCPRIV *infoPtr)
{
 HWND hwnd = GetDlgItem(infoPtr->hwndSelf, IDC_COLOR_LUMBAR);
 RECT rect, client;
 int lum, ldif, ydif;
 HBRUSH hbrush;
 HDC hDC;

 if (IsWindowVisible(hwnd))
 {
  hDC = GetDC(hwnd);
  GetClientRect(hwnd, &client);
  rect = client;

  ldif = 240 / YSTEPS;
  ydif = client.bottom / YSTEPS+1;
  for (lum = 0; lum < 240 + ldif; lum += ldif)
  {
   rect.top = max(0, rect.bottom - ydif);
   hbrush = CreateSolidBrush(CC_HSLtoRGB(infoPtr->h, infoPtr->s, lum));
   FillRect(hDC, &rect, hbrush);
   DeleteObject(hbrush);
   rect.bottom = rect.top;
  }
  GetClientRect(hwnd, &rect);
  DrawEdge(hDC, &rect, BDR_SUNKENOUTER, BF_RECT);
  ReleaseDC(hwnd, hDC);
 }
}