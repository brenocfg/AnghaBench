#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct vo_x11_state {int /*<<< orphan*/  window; int /*<<< orphan*/  display; scalar_t__ parent; } ;
struct vo {struct vo_x11_state* x11; struct mp_vo_opts* opts; } ;
struct TYPE_8__ {scalar_t__ xy_valid; } ;
struct mp_vo_opts {scalar_t__ screen_id; scalar_t__ keepaspect_window; scalar_t__ keepaspect; scalar_t__ force_window_position; TYPE_1__ geometry; } ;
struct mp_rect {int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_11__ {int flags; int min_width; int min_height; int /*<<< orphan*/  win_gravity; int /*<<< orphan*/  height; TYPE_3__ max_aspect; int /*<<< orphan*/  width; TYPE_2__ min_aspect; scalar_t__ max_height; scalar_t__ max_width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_4__ XSizeHints ;

/* Variables and functions */
 int /*<<< orphan*/  CenterGravity ; 
 int PAspect ; 
 int PMinSize ; 
 int PPosition ; 
 int PSize ; 
 int PWinGravity ; 
 int /*<<< orphan*/  RC_H (struct mp_rect) ; 
 int /*<<< orphan*/  RC_W (struct mp_rect) ; 
 TYPE_4__* XAllocSizeHints () ; 
 int /*<<< orphan*/  XFree (TYPE_4__*) ; 
 int /*<<< orphan*/  XSetWMNormalHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void vo_x11_sizehint(struct vo *vo, struct mp_rect rc, bool override_pos)
{
    struct mp_vo_opts *opts = vo->opts;
    struct vo_x11_state *x11 = vo->x11;

    if (!x11->window || x11->parent)
        return;

    bool force_pos = opts->geometry.xy_valid ||     // explicitly forced by user
                     opts->force_window_position || // resize -> reset position
                     opts->screen_id >= 0 ||        // force onto screen area
                     x11->parent ||                 // force to fill parent
                     override_pos;                  // for fullscreen and such

    XSizeHints *hint = XAllocSizeHints();
    if (!hint)
        return; // OOM

    hint->flags |= PSize | (force_pos ? PPosition : 0);
    hint->x = rc.x0;
    hint->y = rc.y0;
    hint->width = RC_W(rc);
    hint->height = RC_H(rc);
    hint->max_width = 0;
    hint->max_height = 0;

    if (opts->keepaspect && opts->keepaspect_window) {
        hint->flags |= PAspect;
        hint->min_aspect.x = hint->width;
        hint->min_aspect.y = hint->height;
        hint->max_aspect.x = hint->width;
        hint->max_aspect.y = hint->height;
    }

    // Set minimum height/width to 4 to avoid off-by-one errors.
    hint->flags |= PMinSize;
    hint->min_width = hint->min_height = 4;

    // This will use the top/left corner of the window for positioning, instead
    // of the top/left corner of the client. _NET_MOVERESIZE_WINDOW could be
    // used to get a different reference point, while keeping gravity.
    hint->flags |= PWinGravity;
    hint->win_gravity = CenterGravity;

    XSetWMNormalHints(x11->display, x11->window, hint);
    XFree(hint);
}