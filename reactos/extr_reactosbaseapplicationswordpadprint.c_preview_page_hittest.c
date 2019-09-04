#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_6__ {scalar_t__ cx; scalar_t__ cy; } ;
struct TYPE_9__ {int pages_shown; int /*<<< orphan*/  page; TYPE_2__ spacing; TYPE_1__ bmScaledSize; } ;
struct TYPE_8__ {scalar_t__ right; scalar_t__ left; scalar_t__ top; scalar_t__ bottom; } ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  POINT ;

/* Variables and functions */
 scalar_t__ PtInRect (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_last_preview_page (int /*<<< orphan*/ ) ; 
 TYPE_4__ preview ; 

__attribute__((used)) static int preview_page_hittest(POINT pt)
{
    RECT rc;
    rc.left = preview.spacing.cx;
    rc.right = rc.left + preview.bmScaledSize.cx;
    rc.top = preview.spacing.cy;
    rc.bottom = rc.top + preview.bmScaledSize.cy;
    if (PtInRect(&rc, pt))
        return 1;

    if (preview.pages_shown <= 1)
        return 0;

    rc.left += preview.bmScaledSize.cx + preview.spacing.cx;
    rc.right += preview.bmScaledSize.cx + preview.spacing.cx;
    if (PtInRect(&rc, pt))
        return is_last_preview_page(preview.page) ? 1 : 2;

    return 0;
}