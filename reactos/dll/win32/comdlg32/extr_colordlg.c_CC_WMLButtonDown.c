#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* lpcc; void* l; void* s; void* h; int /*<<< orphan*/  hwndSelf; void* capturedGraph; } ;
struct TYPE_11__ {int /*<<< orphan*/  rgbResult; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  CC_EditSetHSL (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_EditSetRGB (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_HSLtoRGB (void*,void*,void*) ; 
 scalar_t__ CC_MouseCheckColorGraph (int /*<<< orphan*/ ,void*,void**,void**,int /*<<< orphan*/ ) ; 
 scalar_t__ CC_MouseCheckPredefColorArray (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CC_MouseCheckUserColorArray (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CC_PaintCross (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_PaintSelectedColor (TYPE_2__*) ; 
 int /*<<< orphan*/  CC_PaintTriangle (TYPE_2__*) ; 
 void* CC_RGBtoHSL (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 void* IDC_COLOR_GRAPH ; 
 void* IDC_COLOR_LUMBAR ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT CC_WMLButtonDown( CCPRIV *infoPtr, LPARAM lParam )
{
   int i = 0;

   if (CC_MouseCheckPredefColorArray(infoPtr, 6, 8, lParam))
      i = 1;
   else
      if (CC_MouseCheckUserColorArray(infoPtr, 2, 8, lParam))
         i = 1;
      else
	 if (CC_MouseCheckColorGraph(infoPtr->hwndSelf, IDC_COLOR_GRAPH, &infoPtr->h, &infoPtr->s, lParam))
         {
	    i = 2;
            infoPtr->capturedGraph = IDC_COLOR_GRAPH;
         }
	 else
	    if (CC_MouseCheckColorGraph(infoPtr->hwndSelf, IDC_COLOR_LUMBAR, NULL, &infoPtr->l, lParam))
            {
	       i = 2;
               infoPtr->capturedGraph = IDC_COLOR_LUMBAR;
            }
   if ( i == 2 )
   {
      SetCapture(infoPtr->hwndSelf);
      infoPtr->lpcc->rgbResult = CC_HSLtoRGB(infoPtr->h, infoPtr->s, infoPtr->l);
   }
   if ( i == 1 )
   {
      infoPtr->h = CC_RGBtoHSL('H', infoPtr->lpcc->rgbResult);
      infoPtr->s = CC_RGBtoHSL('S', infoPtr->lpcc->rgbResult);
      infoPtr->l = CC_RGBtoHSL('L', infoPtr->lpcc->rgbResult);
   }
   if (i)
   {
      CC_EditSetRGB(infoPtr);
      CC_EditSetHSL(infoPtr);
      CC_PaintCross(infoPtr);
      CC_PaintTriangle(infoPtr);
      CC_PaintSelectedColor(infoPtr);
      return TRUE;
   }
   return FALSE;
}