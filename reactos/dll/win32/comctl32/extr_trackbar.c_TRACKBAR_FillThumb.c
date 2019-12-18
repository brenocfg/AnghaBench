#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int x; int y; } ;
struct TYPE_9__ {int bottom; int top; int right; int left; } ;
struct TYPE_8__ {int dwStyle; TYPE_2__ rcThumb; } ;
typedef  TYPE_1__ TRACKBAR_INFO ;
typedef  TYPE_2__ RECT ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Polygon (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPolyFillMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TBS_BOTH ; 
 int TBS_LEFT ; 
 int TBS_TOP ; 
 int TBS_VERT ; 
 int /*<<< orphan*/  WINDING ; 

__attribute__((used)) static int
TRACKBAR_FillThumb (const TRACKBAR_INFO *infoPtr, HDC hdc, HBRUSH hbrush)
{
    const RECT *thumb = &infoPtr->rcThumb;
    POINT points[6];
    int PointDepth;
    HBRUSH oldbr;

    if (infoPtr->dwStyle & TBS_BOTH)
    {
        FillRect(hdc, thumb, hbrush);
        return 0;
    }

    if (infoPtr->dwStyle & TBS_VERT)
    {
        PointDepth = (thumb->bottom - thumb->top) / 2;
        if (infoPtr->dwStyle & TBS_LEFT)
        {
            points[0].x = thumb->right-1;
            points[0].y = thumb->top;
            points[1].x = thumb->right-1;
            points[1].y = thumb->bottom-1;
            points[2].x = thumb->left + PointDepth;
            points[2].y = thumb->bottom-1;
            points[3].x = thumb->left;
            points[3].y = thumb->top + PointDepth;
            points[4].x = thumb->left + PointDepth;
            points[4].y = thumb->top;
            points[5].x = points[0].x;
            points[5].y = points[0].y;
        }
        else
        {
            points[0].x = thumb->right;
            points[0].y = thumb->top + PointDepth;
            points[1].x = thumb->right - PointDepth;
            points[1].y = thumb->bottom-1;
            points[2].x = thumb->left;
            points[2].y = thumb->bottom-1;
            points[3].x = thumb->left;
            points[3].y = thumb->top;
            points[4].x = thumb->right - PointDepth;
            points[4].y = thumb->top;
            points[5].x = points[0].x;
            points[5].y = points[0].y;
        }
    }
    else
    {
        PointDepth = (thumb->right - thumb->left) / 2;
        if (infoPtr->dwStyle & TBS_TOP)
        {
            points[0].x = thumb->left + PointDepth;
            points[0].y = thumb->top+1;
            points[1].x = thumb->right-1;
            points[1].y = thumb->top + PointDepth + 1;
            points[2].x = thumb->right-1;
            points[2].y = thumb->bottom-1;
            points[3].x = thumb->left;
            points[3].y = thumb->bottom-1;
            points[4].x = thumb->left;
            points[4].y = thumb->top + PointDepth + 1;
            points[5].x = points[0].x;
            points[5].y = points[0].y;
        }
        else
        {
            points[0].x = thumb->right-1;
            points[0].y = thumb->top;
            points[1].x = thumb->right-1;
            points[1].y = thumb->bottom - PointDepth - 1;
            points[2].x = thumb->left + PointDepth;
            points[2].y = thumb->bottom-1;
            points[3].x = thumb->left;
            points[3].y = thumb->bottom - PointDepth - 1;
            points[4].x = thumb->left;
            points[4].y = thumb->top;
            points[5].x = points[0].x;
            points[5].y = points[0].y;
        }
    }

    oldbr = SelectObject(hdc, hbrush);
    SetPolyFillMode(hdc, WINDING);
    Polygon(hdc, points, ARRAY_SIZE(points));
    SelectObject(hdc, oldbr);

    return PointDepth;
}