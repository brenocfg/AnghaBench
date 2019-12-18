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
struct vo_x11_state {scalar_t__ window; scalar_t__ colormap; int mouse_cursor_set; int mouse_cursor_visible; scalar_t__ parent; scalar_t__ xim; scalar_t__ xic; int /*<<< orphan*/  display; scalar_t__ rootwin; int /*<<< orphan*/  screen; } ;
struct vo {struct vo_x11_state* x11; } ;
struct mp_rect {int /*<<< orphan*/  y0; int /*<<< orphan*/  x0; } ;
struct TYPE_8__ {int /*<<< orphan*/  depth; } ;
typedef  TYPE_1__ XWindowAttributes ;
struct TYPE_9__ {int /*<<< orphan*/  visual; int /*<<< orphan*/  depth; } ;
typedef  TYPE_2__ XVisualInfo ;
struct TYPE_10__ {scalar_t__ colormap; int /*<<< orphan*/  border_pixel; } ;
typedef  TYPE_3__ XSetWindowAttributes ;
typedef  scalar_t__ Window ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  AllocNone ; 
 unsigned long CWBorderPixel ; 
 unsigned long CWColormap ; 
 int /*<<< orphan*/  CopyFromParent ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  RC_H (struct mp_rect) ; 
 int /*<<< orphan*/  RC_W (struct mp_rect) ; 
 int /*<<< orphan*/  TrueColor ; 
 int /*<<< orphan*/  WM_DELETE_WINDOW ; 
 int /*<<< orphan*/  XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ XCreateColormap (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XCreateIC (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ XCreateWindow (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,TYPE_3__*) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int XIMPreeditNone ; 
 int XIMStatusNone ; 
 int /*<<< orphan*/  XMatchVisualInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  XNClientWindow ; 
 int /*<<< orphan*/  XNFocusWindow ; 
 int /*<<< orphan*/  XNInputStyle ; 
 int /*<<< orphan*/  XSetWMProtocols (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _GTK_THEME_VARIANT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vo_update_cursor (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_dnd_init_window (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_set_property_utf8 (struct vo*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vo_x11_set_wm_icon (struct vo_x11_state*) ; 
 int /*<<< orphan*/  vo_x11_update_composition_hint (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_update_window_title (struct vo*) ; 
 int /*<<< orphan*/  vo_x11_xembed_update (struct vo_x11_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vo_x11_create_window(struct vo *vo, XVisualInfo *vis,
                                 struct mp_rect rc)
{
    struct vo_x11_state *x11 = vo->x11;

    assert(x11->window == None);
    assert(!x11->xic);

    XVisualInfo vinfo_storage;
    if (!vis) {
        vis = &vinfo_storage;
        XWindowAttributes att;
        XGetWindowAttributes(x11->display, x11->rootwin, &att);
        XMatchVisualInfo(x11->display, x11->screen, att.depth, TrueColor, vis);
    }

    if (x11->colormap == None) {
        x11->colormap = XCreateColormap(x11->display, x11->rootwin,
                                        vis->visual, AllocNone);
    }

    unsigned long xswamask = CWBorderPixel | CWColormap;
    XSetWindowAttributes xswa = {
        .border_pixel = 0,
        .colormap = x11->colormap,
    };

    Window parent = x11->parent;
    if (!parent)
        parent = x11->rootwin;

    x11->window =
        XCreateWindow(x11->display, parent, rc.x0, rc.y0, RC_W(rc), RC_H(rc), 0,
                      vis->depth, CopyFromParent, vis->visual, xswamask, &xswa);
    Atom protos[1] = {XA(x11, WM_DELETE_WINDOW)};
    XSetWMProtocols(x11->display, x11->window, protos, 1);

    x11->mouse_cursor_set = false;
    x11->mouse_cursor_visible = true;
    vo_update_cursor(vo);

    if (x11->xim) {
        x11->xic = XCreateIC(x11->xim,
                             XNInputStyle, XIMPreeditNone | XIMStatusNone,
                             XNClientWindow, x11->window,
                             XNFocusWindow, x11->window,
                             NULL);
    }

    if (!x11->parent) {
        vo_x11_update_composition_hint(vo);
        vo_x11_set_wm_icon(x11);
        vo_x11_update_window_title(vo);
        vo_x11_dnd_init_window(vo);
        vo_x11_set_property_utf8(vo, XA(x11, _GTK_THEME_VARIANT), "dark");
    }
    vo_x11_xembed_update(x11, 0);
}