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
typedef  scalar_t__ uint64_t ;
struct timespec {long long tv_sec; int tv_nsec; } ;
struct oml_sync {int state_ok; scalar_t__ user_sbc; scalar_t__ last_ust; scalar_t__ last_msc; scalar_t__ last_sbc; scalar_t__ vsync_duration; scalar_t__ last_sbc_mp_time; scalar_t__ last_queue_display_time; scalar_t__ last_skipped_vsyncs; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  oml_sync_reset (struct oml_sync*) ; 

void oml_sync_swap(struct oml_sync *oml, int64_t ust, int64_t msc, int64_t sbc)
{
    if (!oml->state_ok)
        oml_sync_reset(oml);

    oml->last_skipped_vsyncs = 0;
    oml->user_sbc += 1;

    if (sbc < 0)
        return;

    oml->state_ok = true;

    int64_t ust_passed = oml->last_ust ? ust - oml->last_ust : 0;
    oml->last_ust = ust;

    int64_t msc_passed = oml->last_msc ? msc - oml->last_msc : 0;
    oml->last_msc = msc;

    int64_t sbc_passed = sbc - oml->last_sbc;
    oml->last_sbc = sbc;

    // Display frame duration. This makes assumptions about UST (see below).
    if (msc_passed && ust_passed)
        oml->vsync_duration = ust_passed / msc_passed;

    // Only if a new frame was displayed (sbc increased) we have sort-of a
    // chance that the current (ust, msc) is for the sbc. But this is racy,
    // because skipped frames drops could have increased the msc right after the
    // display event and before we queried the values. This code hopes for the
    // best and ignores this.
    if (sbc_passed) {
        // The GLX extension spec doesn't define what the UST is (not even its
        // unit). Simply assume UST is a simple CLOCK_MONOTONIC usec value. This
        // is what Mesa does, and what the Google EGL extension seems to imply
        // (they mention CLOCK_MONOTONIC, but not the unit).
        // The swap buffer call happened "some" but very small time ago, so we
        // can get away with querying the current time. There is also the
        // implicit assumption that mpv's timer and the UST use the same clock
        // (which it does on POSIX).
        struct timespec ts;
        if (clock_gettime(CLOCK_MONOTONIC, &ts))
            return;
        uint64_t now_monotonic = ts.tv_sec * 1000000LL + ts.tv_nsec / 1000;
        uint64_t ust_mp_time = mp_time_us() - (now_monotonic - ust);

        // Assume this is exactly when the actual display event for this sbc
        // happened. This is subject to the race mentioned above.
        oml->last_sbc_mp_time = ust_mp_time;
    }

    // At least one frame needs to be actually displayed before
    // oml->last_sbc_mp_time is set.
    if (!sbc)
        return;

    // Extrapolate from the last sbc time (when a frame was actually displayed),
    // and by adding the number of frames that were queued since to it.
    // For every unit the sbc is smaller than user_sbc, the actual display
    // is one frame ahead (assumes oml_sync_swap() is called for every
    // vsync).
    oml->last_queue_display_time =
        oml->last_sbc_mp_time + (oml->user_sbc - sbc) * oml->vsync_duration;
}