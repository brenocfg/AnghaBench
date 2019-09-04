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
struct vo_wayland_state {int /*<<< orphan*/  xkb_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct vo_wayland_state*,char*) ; 
 int /*<<< orphan*/  XKB_CONTEXT_NO_FLAGS ; 
 int /*<<< orphan*/  xkb_context_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool create_input(struct vo_wayland_state *wl)
{
    wl->xkb_context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);

    if (!wl->xkb_context) {
        MP_ERR(wl, "failed to initialize input: check xkbcommon\n");
        return 1;
    }

    return 0;
}