#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vo_w32_state {scalar_t__ monitor; double display_fps; char* color_profile; int /*<<< orphan*/  window; } ;
struct TYPE_2__ {int cbSize; int /*<<< orphan*/  szDevice; } ;
typedef  TYPE_1__ MONITORINFOEXW ;
typedef  int /*<<< orphan*/  MONITORINFO ;
typedef  scalar_t__ HMONITOR ;

/* Variables and functions */
 int /*<<< orphan*/  GetMonitorInfoW (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MONITOR_DEFAULTTOPRIMARY ; 
 int /*<<< orphan*/  MP_VERBOSE (struct vo_w32_state*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct vo_w32_state*,char*) ; 
 scalar_t__ MonitorFromWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VO_EVENT_ICC_PROFILE_CHANGED ; 
 int /*<<< orphan*/  VO_EVENT_WIN_STATE ; 
 char* get_color_profile (struct vo_w32_state*,int /*<<< orphan*/ ) ; 
 double get_refresh_rate_from_gdi (int /*<<< orphan*/ ) ; 
 double mp_w32_displayconfig_get_refresh_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_events (struct vo_w32_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 int /*<<< orphan*/  update_dpi (struct vo_w32_state*) ; 

__attribute__((used)) static void update_display_info(struct vo_w32_state *w32)
{
    HMONITOR monitor = MonitorFromWindow(w32->window, MONITOR_DEFAULTTOPRIMARY);
    if (w32->monitor == monitor)
        return;
    w32->monitor = monitor;

    update_dpi(w32);

    MONITORINFOEXW mi = { .cbSize = sizeof mi };
    GetMonitorInfoW(monitor, (MONITORINFO*)&mi);

    // Try to get the monitor refresh rate.
    double freq = 0.0;

    if (freq == 0.0)
        freq = mp_w32_displayconfig_get_refresh_rate(mi.szDevice);
    if (freq == 0.0)
        freq = get_refresh_rate_from_gdi(mi.szDevice);

    if (freq != w32->display_fps) {
        MP_VERBOSE(w32, "display-fps: %f\n", freq);
        if (freq == 0.0)
            MP_WARN(w32, "Couldn't determine monitor refresh rate\n");
        w32->display_fps = freq;
        signal_events(w32, VO_EVENT_WIN_STATE);
    }

    char *color_profile = get_color_profile(w32, mi.szDevice);
    if ((color_profile == NULL) != (w32->color_profile == NULL) ||
        (color_profile && strcmp(color_profile, w32->color_profile)))
    {
        if (color_profile)
            MP_VERBOSE(w32, "color-profile: %s\n", color_profile);
        talloc_free(w32->color_profile);
        w32->color_profile = color_profile;
        color_profile = NULL;
        signal_events(w32, VO_EVENT_ICC_PROFILE_CHANGED);
    }

    talloc_free(color_profile);
}