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
struct vo_x11_state {int screensaver_enabled; int dpms_touched; int /*<<< orphan*/ * display; } ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  CARD16 ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DPMSDisable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPMSEnable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPMSInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ DPMSQueryExtension (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo_x11_state*,char*,char*) ; 
 int /*<<< orphan*/  MP_WARN (struct vo_x11_state*,char*) ; 
 scalar_t__ xss_suspend (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void set_screensaver(struct vo_x11_state *x11, bool enabled)
{
    Display *mDisplay = x11->display;
    if (!mDisplay || x11->screensaver_enabled == enabled)
        return;
    MP_VERBOSE(x11, "%s screensaver.\n", enabled ? "Enabling" : "Disabling");
    x11->screensaver_enabled = enabled;
    if (xss_suspend(mDisplay, !enabled))
        return;
    int nothing;
    if (DPMSQueryExtension(mDisplay, &nothing, &nothing)) {
        BOOL onoff = 0;
        CARD16 state;
        DPMSInfo(mDisplay, &state, &onoff);
        if (!x11->dpms_touched && enabled)
            return; // enable DPMS only we we disabled it before
        if (enabled != !!onoff) {
            MP_VERBOSE(x11, "Setting DMPS: %s.\n", enabled ? "on" : "off");
            if (enabled) {
                DPMSEnable(mDisplay);
            } else {
                DPMSDisable(mDisplay);
                x11->dpms_touched = true;
            }
            DPMSInfo(mDisplay, &state, &onoff);
            if (enabled != !!onoff)
                MP_WARN(x11, "DPMS state could not be set.\n");
        }
    }
}