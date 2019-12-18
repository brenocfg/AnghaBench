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
struct TYPE_10__ {float right; float left; float bottom; float top; } ;
typedef  TYPE_1__ RECT ;
typedef  float LONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IntersectRect (TYPE_1__*,TYPE_1__*,TYPE_1__ const*) ; 
 scalar_t__ IsRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL wined3d_clip_blit(const RECT *clip_rect, RECT *clipped, RECT *other)
{
    RECT orig = *clipped;
    float scale_x = (float)(orig.right - orig.left) / (float)(other->right - other->left);
    float scale_y = (float)(orig.bottom - orig.top) / (float)(other->bottom - other->top);

    IntersectRect(clipped, clipped, clip_rect);

    if (IsRectEmpty(clipped))
    {
        SetRectEmpty(other);
        return FALSE;
    }

    other->left += (LONG)((clipped->left - orig.left) / scale_x);
    other->top += (LONG)((clipped->top - orig.top) / scale_y);
    other->right -= (LONG)((orig.right - clipped->right) / scale_x);
    other->bottom -= (LONG)((orig.bottom - clipped->bottom) / scale_y);

    return TRUE;
}