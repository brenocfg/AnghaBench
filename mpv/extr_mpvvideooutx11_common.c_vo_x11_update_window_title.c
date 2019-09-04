#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vo_x11_state {int /*<<< orphan*/  window_title; int /*<<< orphan*/  window; } ;
struct vo {struct vo_x11_state* x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_WM_ICON_NAME ; 
 int /*<<< orphan*/  XA_WM_NAME ; 
 int /*<<< orphan*/  _NET_WM_ICON_NAME ; 
 int /*<<< orphan*/  _NET_WM_NAME ; 
 int /*<<< orphan*/  vo_x11_set_property_string (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vo_x11_set_property_utf8 (struct vo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vo_x11_update_window_title(struct vo *vo)
{
    struct vo_x11_state *x11 = vo->x11;

    if (!x11->window || !x11->window_title)
        return;

    vo_x11_set_property_string(vo, XA_WM_NAME, x11->window_title);
    vo_x11_set_property_string(vo, XA_WM_ICON_NAME, x11->window_title);
    vo_x11_set_property_utf8(vo, XA(x11, _NET_WM_NAME), x11->window_title);
    vo_x11_set_property_utf8(vo, XA(x11, _NET_WM_ICON_NAME), x11->window_title);
}