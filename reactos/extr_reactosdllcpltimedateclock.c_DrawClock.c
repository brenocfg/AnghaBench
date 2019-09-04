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
struct TYPE_6__ {int /*<<< orphan*/ * hGreyPen; int /*<<< orphan*/  cyClient; int /*<<< orphan*/  cxClient; int /*<<< orphan*/ * hGreyBrush; } ;
struct TYPE_5__ {int x; int y; } ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__* PCLOCKDATA ;
typedef  int INT ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/ * HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_PEN ; 
 int /*<<< orphan*/  Ellipse (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/ * GetCurrentObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJ_PEN ; 
 int /*<<< orphan*/  RotatePoint (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/ * SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT
DrawClock(HDC hdc, PCLOCKDATA pClockData)
{
     INT iAngle,Radius;
     POINT pt[3];
     HBRUSH hBrushOld;
     HPEN hPenOld = NULL;

     /* Grey brush to fill the dots */
     hBrushOld = SelectObject(hdc, pClockData->hGreyBrush);

     hPenOld = GetCurrentObject(hdc, OBJ_PEN);

     // TODO: Check if this conversion is correct resp. usable
     Radius = min(pClockData->cxClient,pClockData->cyClient) * 2;

     for (iAngle = 0; iAngle < 360; iAngle += 6)
     {
          /* Starting coords */
          pt[0].x = 0;
          pt[0].y = Radius;

          /* Rotate start coords */
          RotatePoint(pt, 1, iAngle);

          /* Determine whether it's a big dot or a little dot
           * i.e. 1-4 or 5, 6-9 or 10, 11-14 or 15 */
          if (iAngle % 5)
          {
                pt[2].x = pt[2].y = 7;
                SelectObject(hdc, pClockData->hGreyPen);
          }
          else
          {
              pt[2].x = pt[2].y = 16;
              SelectObject(hdc, GetStockObject(BLACK_PEN));
          }

          pt[0].x -= pt[2].x / 2;
          pt[0].y -= pt[2].y / 2;

          pt[1].x  = pt[0].x + pt[2].x;
          pt[1].y  = pt[0].y + pt[2].y;

          Ellipse(hdc, pt[0].x, pt[0].y, pt[1].x, pt[1].y);
     }

     SelectObject(hdc, hBrushOld);
     SelectObject(hdc, hPenOld);
     return Radius;
}