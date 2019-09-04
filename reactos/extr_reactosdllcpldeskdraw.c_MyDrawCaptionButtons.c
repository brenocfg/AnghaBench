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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int right; scalar_t__ bottom; scalar_t__ top; } ;
struct TYPE_5__ {int left; int right; scalar_t__ bottom; scalar_t__ top; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__* LPRECT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLOR_SCHEME ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DFCS_CAPTIONCLOSE ; 
 int /*<<< orphan*/  DFCS_CAPTIONMAX ; 
 int /*<<< orphan*/  DFCS_CAPTIONMIN ; 
 int /*<<< orphan*/  DFC_CAPTION ; 
 int /*<<< orphan*/  MyDrawFrameControl (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

VOID
MyDrawCaptionButtons(HDC hdc, LPRECT lpRect, BOOL bMinMax, int x, COLOR_SCHEME *scheme)
{
    RECT rc3;
    RECT rc4;
    RECT rc5;

    rc3.left = lpRect->right - 2 - x;
    rc3.top = lpRect->top + 2;
    rc3.right = lpRect->right - 2;
    rc3.bottom = lpRect->bottom - 2;

    MyDrawFrameControl(hdc, &rc3, DFC_CAPTION, DFCS_CAPTIONCLOSE, scheme);

    if (bMinMax)
    {
        rc4.left = rc3.left - x - 2;
        rc4.top = rc3.top;
        rc4.right = rc3.right - x - 2;
        rc4.bottom = rc3.bottom;

        MyDrawFrameControl(hdc, &rc4, DFC_CAPTION, DFCS_CAPTIONMAX, scheme);

        rc5.left = rc4.left - x;
        rc5.top = rc4.top;
        rc5.right = rc4.right - x;
        rc5.bottom = rc4.bottom;

        MyDrawFrameControl(hdc, &rc5, DFC_CAPTION, DFCS_CAPTIONMIN, scheme);
    }
}