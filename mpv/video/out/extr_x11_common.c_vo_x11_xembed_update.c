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
struct vo_x11_state {int /*<<< orphan*/  window; int /*<<< orphan*/  display; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  XA (struct vo_x11_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 
 int XEMBED_VERSION ; 
 int /*<<< orphan*/  _XEMBED_INFO ; 

__attribute__((used)) static void vo_x11_xembed_update(struct vo_x11_state *x11, int flags)
{
    if (!x11->window || !x11->parent)
        return;

    long xembed_info[] = {XEMBED_VERSION, flags};
    Atom name = XA(x11, _XEMBED_INFO);
    XChangeProperty(x11->display, x11->window, name, name, 32,
                    PropModeReplace, (char *)xembed_info, 2);
}