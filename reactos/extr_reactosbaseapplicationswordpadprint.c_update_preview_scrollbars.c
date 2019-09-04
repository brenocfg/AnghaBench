#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sbi ;
struct TYPE_8__ {int cx; int cy; } ;
struct TYPE_11__ {scalar_t__ zoomlevel; int pages_shown; TYPE_1__ bmScaledSize; } ;
struct TYPE_10__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_9__ {int cbSize; int fMask; int nMax; int /*<<< orphan*/  nPage; scalar_t__ nMin; } ;
typedef  TYPE_2__ SCROLLINFO ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int SIF_PAGE ; 
 int SIF_RANGE ; 
 int /*<<< orphan*/  SetScrollInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int min_spacing ; 
 TYPE_5__ preview ; 

__attribute__((used)) static void update_preview_scrollbars(HWND hwndPreview, RECT *window)
{
    SCROLLINFO sbi;
    sbi.cbSize = sizeof(sbi);
    sbi.fMask = SIF_PAGE|SIF_RANGE;
    sbi.nMin = 0;
    if (preview.zoomlevel == 0)
    {
        /* Hide scrollbars when zoomed out. */
        sbi.nMax = 0;
        sbi.nPage = window->right;
        SetScrollInfo(hwndPreview, SB_HORZ, &sbi, TRUE);
        sbi.nPage = window->bottom;
        SetScrollInfo(hwndPreview, SB_VERT, &sbi, TRUE);
    } else {
        sbi.nMax = preview.bmScaledSize.cx * preview.pages_shown +
                   min_spacing * (preview.pages_shown + 1);
        sbi.nPage = window->right;
        SetScrollInfo(hwndPreview, SB_HORZ, &sbi, TRUE);
        /* Change in the horizontal scrollbar visibility affects the
         * client rect, so update the client rect. */
        GetClientRect(hwndPreview, window);
        sbi.nMax = preview.bmScaledSize.cy + min_spacing * 2;
        sbi.nPage = window->bottom;
        SetScrollInfo(hwndPreview, SB_VERT, &sbi, TRUE);
    }
}