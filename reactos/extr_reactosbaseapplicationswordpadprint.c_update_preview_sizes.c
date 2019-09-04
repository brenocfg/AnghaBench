#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cx; int /*<<< orphan*/  cy; } ;
struct TYPE_9__ {int cx; int cy; } ;
struct TYPE_8__ {int cy; float cx; } ;
struct TYPE_12__ {int zoomlevel; int pages_shown; float zoomratio; TYPE_3__ spacing; TYPE_2__ bmScaledSize; TYPE_1__ bmSize; } ;
struct TYPE_11__ {int bottom; int right; } ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int min_spacing ; 
 TYPE_6__ preview ; 
 int /*<<< orphan*/  update_preview_scrollbars (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void update_preview_sizes(HWND hwndPreview, BOOL zoomLevelUpdated)
{
    RECT window;

    GetClientRect(hwndPreview, &window);

    /* The zoom ratio isn't updated for partial zoom because of resizing the window. */
    if (zoomLevelUpdated || preview.zoomlevel != 1)
    {
        float ratio, ratioHeight, ratioWidth;
        if (preview.zoomlevel == 2)
        {
            ratio = 1.0;
        } else {
            ratioHeight = (window.bottom - min_spacing * 2) / (float)preview.bmSize.cy;

            ratioWidth = (float)(window.right -
                                 min_spacing * (preview.pages_shown + 1)) /
                         (preview.pages_shown * preview.bmSize.cx);

            if(ratioWidth > ratioHeight)
                ratio = ratioHeight;
            else
                ratio = ratioWidth;

            if (preview.zoomlevel == 1)
                ratio += (1.0 - ratio) / 2;
        }
        preview.zoomratio = ratio;
    }

    preview.bmScaledSize.cx = preview.bmSize.cx * preview.zoomratio;
    preview.bmScaledSize.cy = preview.bmSize.cy * preview.zoomratio;

    preview.spacing.cy = max(min_spacing, (window.bottom - preview.bmScaledSize.cy) / 2);

    preview.spacing.cx = (window.right -
                          preview.bmScaledSize.cx * preview.pages_shown) /
                         (preview.pages_shown + 1);
    if (preview.spacing.cx < min_spacing)
        preview.spacing.cx = min_spacing;

    update_preview_scrollbars(hwndPreview, &window);
}