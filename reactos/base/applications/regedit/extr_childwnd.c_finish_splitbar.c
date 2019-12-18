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
struct TYPE_5__ {int nSplitPos; } ;
struct TYPE_4__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  ResizeWnd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_splitbar (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* g_pChildWnd ; 
 int last_split ; 

__attribute__((used)) static void finish_splitbar(HWND hWnd, int x)
{
    RECT rt;

    draw_splitbar(hWnd, last_split);
    last_split = -1;
    GetClientRect(hWnd, &rt);
    g_pChildWnd->nSplitPos = x;
    ResizeWnd(rt.right, rt.bottom);
    ReleaseCapture();
}