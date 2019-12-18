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
typedef  long long uint64_t ;
struct vo_wayland_state {int sync_size; scalar_t__ last_ust; int last_msc; int last_sbc; int vsync_duration; long long last_sbc_mp_time; long long last_queue_display_time; TYPE_1__* sync; scalar_t__ last_skipped_vsyncs; } ;
struct timespec {long long tv_sec; int tv_nsec; } ;
typedef  int int64_t ;
struct TYPE_2__ {scalar_t__ ust; scalar_t__ refresh_usec; int msc; int sbc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 long long mp_time_us () ; 

void wayland_sync_swap(struct vo_wayland_state *wl)
{
    int index = wl->sync_size - 1;

    wl->last_skipped_vsyncs = 0;

    // If these are the same (can happen if a frame takes too long), update
    // the ust/msc/sbc based on when the next frame is expected to arrive.
    if (wl->sync[index].ust == wl->last_ust && wl->last_ust) {
        wl->sync[index].ust += wl->sync[index].refresh_usec;
        wl->sync[index].msc += 1;
        wl->sync[index].sbc += 1;
    }

    int64_t ust_passed = wl->sync[index].ust ? wl->sync[index].ust - wl->last_ust: 0;
    wl->last_ust = wl->sync[index].ust;
    int64_t msc_passed = wl->sync[index].msc ? wl->sync[index].msc - wl->last_msc: 0;
    wl->last_msc = wl->sync[index].msc;
    int64_t sbc_passed = wl->sync[index].sbc ? wl->sync[index].sbc - wl->last_sbc: 0;
    wl->last_sbc = wl->sync[index].sbc;

    if (msc_passed && ust_passed)
        wl->vsync_duration = ust_passed / msc_passed;

    if (sbc_passed) {
        struct timespec ts;
        if (clock_gettime(CLOCK_MONOTONIC, &ts)) {
            return;
        }

        uint64_t now_monotonic = ts.tv_sec * 1000000LL + ts.tv_nsec / 1000;
        uint64_t ust_mp_time = mp_time_us() - (now_monotonic - wl->sync[index].ust);
        wl->last_sbc_mp_time = ust_mp_time;
    }

    if (!wl->sync[index].sbc)
        return;

    wl->last_queue_display_time = wl->last_sbc_mp_time + sbc_passed*wl->vsync_duration;
}