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
struct zwp_idle_inhibit_manager_v1 {int dummy; } ;
struct vo_wayland_state {int /*<<< orphan*/ * idle_inhibitor; int /*<<< orphan*/  surface; struct zwp_idle_inhibit_manager_v1* idle_inhibit_manager; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_VERBOSE (struct vo_wayland_state*,char*) ; 
 int VO_NOTIMPL ; 
 int VO_TRUE ; 
 int /*<<< orphan*/ * zwp_idle_inhibit_manager_v1_create_inhibitor (struct zwp_idle_inhibit_manager_v1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_idle_inhibitor_v1_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_screensaver_inhibitor(struct vo_wayland_state *wl, int state)
{
    if (!wl->idle_inhibit_manager)
        return VO_NOTIMPL;
    if (state == (!!wl->idle_inhibitor))
        return VO_TRUE;
    if (state) {
        MP_VERBOSE(wl, "Enabling idle inhibitor\n");
        struct zwp_idle_inhibit_manager_v1 *mgr = wl->idle_inhibit_manager;
        wl->idle_inhibitor = zwp_idle_inhibit_manager_v1_create_inhibitor(mgr, wl->surface);
    } else {
        MP_VERBOSE(wl, "Disabling the idle inhibitor\n");
        zwp_idle_inhibitor_v1_destroy(wl->idle_inhibitor);
        wl->idle_inhibitor = NULL;
    }
    return VO_TRUE;
}