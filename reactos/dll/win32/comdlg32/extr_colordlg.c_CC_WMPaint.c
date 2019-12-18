#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CC_PaintColorGraph (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintCross (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintLumBar (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintPredefColorArray (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  CC_PaintSelectedColor (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintTriangle (TYPE_1__*) ; 
 int /*<<< orphan*/  CC_PaintUserColorArray (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT CC_WMPaint( CCPRIV *lpp )
{
    PAINTSTRUCT ps;

    BeginPaint(lpp->hwndSelf, &ps);
    /* we have to paint dialog children except text and buttons */
    CC_PaintPredefColorArray(lpp, 6, 8);
    CC_PaintUserColorArray(lpp, 2, 8);
    CC_PaintLumBar(lpp);
    CC_PaintTriangle(lpp);
    CC_PaintSelectedColor(lpp);
    CC_PaintColorGraph(lpp);
    CC_PaintCross(lpp);
    EndPaint(lpp->hwndSelf, &ps);

    return TRUE;
}