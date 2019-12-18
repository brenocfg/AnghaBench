#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ capturedGraph; int l; int h; int s; TYPE_1__* lpcc; int /*<<< orphan*/  hwndSelf; } ;
struct TYPE_9__ {int /*<<< orphan*/  rgbResult; } ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  CC_EditSetHSL (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_EditSetRGB (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_HSLtoRGB (int,int,int) ; 
 scalar_t__ CC_MouseCheckColorGraph (int /*<<< orphan*/ ,scalar_t__,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_PaintCross (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_PaintSelectedColor (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_PaintTriangle (TYPE_2__*) ; 
 scalar_t__ IDC_COLOR_GRAPH ; 
 int /*<<< orphan*/  ReleaseCapture () ; 

__attribute__((used)) static LRESULT CC_WMMouseMove( CCPRIV *infoPtr, LPARAM lParam )
{
   if (infoPtr->capturedGraph)
   {
      int *ptrh = NULL, *ptrs = &infoPtr->l;
      if (infoPtr->capturedGraph == IDC_COLOR_GRAPH)
      {
          ptrh = &infoPtr->h;
          ptrs = &infoPtr->s;
      }
      if (CC_MouseCheckColorGraph( infoPtr->hwndSelf, infoPtr->capturedGraph, ptrh, ptrs, lParam))
      {
          infoPtr->lpcc->rgbResult = CC_HSLtoRGB(infoPtr->h, infoPtr->s, infoPtr->l);
          CC_EditSetRGB(infoPtr);
          CC_EditSetHSL(infoPtr);
          CC_PaintCross(infoPtr);
          CC_PaintTriangle(infoPtr);
          CC_PaintSelectedColor(infoPtr);
      }
      else
      {
          ReleaseCapture();
          infoPtr->capturedGraph = 0;
      }
      return 1;
   }
   return 0;
}