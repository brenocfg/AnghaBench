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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct wp_presentation_feedback {int dummy; } ;
struct vo_wayland_state {TYPE_1__* sync; int /*<<< orphan*/  user_sbc; } ;
typedef  long long int64_t ;
struct TYPE_2__ {long long ust; int msc; int refresh_usec; int filled; int /*<<< orphan*/  sbc; } ;

/* Variables and functions */
 int last_available_sync (struct vo_wayland_state*) ; 
 int /*<<< orphan*/  queue_new_sync (struct vo_wayland_state*) ; 
 int /*<<< orphan*/  vo_wayland_sync_shift (struct vo_wayland_state*) ; 
 int /*<<< orphan*/  wp_presentation_feedback_destroy (struct wp_presentation_feedback*) ; 

__attribute__((used)) static void feedback_presented(void *data, struct wp_presentation_feedback *fback,
                              uint32_t tv_sec_hi, uint32_t tv_sec_lo,
                              uint32_t tv_nsec, uint32_t refresh_nsec,
                              uint32_t seq_hi, uint32_t seq_lo,
                              uint32_t flags)
{
    struct vo_wayland_state *wl = data;
    wp_presentation_feedback_destroy(fback);
    vo_wayland_sync_shift(wl);

    // Very similar to oml_sync_control, in this case we assume that every
    // time the compositor receives feedback, a buffer swap has been already
    // been performed.
    //
    // Notes:
    //  - tv_sec_lo + tv_sec_hi is the equivalent of oml's ust
    //  - seq_lo + seq_hi is the equivalent of oml's msc
    //  - these values are updated everytime the compositor receives feedback.

    int index = last_available_sync(wl);
    if (index < 0) {
        queue_new_sync(wl);
        index = 0;
    }
    int64_t sec = (uint64_t) tv_sec_lo + ((uint64_t) tv_sec_hi << 32);
    wl->sync[index].sbc = wl->user_sbc;
    wl->sync[index].ust = sec * 1000000LL + (uint64_t) tv_nsec / 1000;
    wl->sync[index].msc = (uint64_t) seq_lo + ((uint64_t) seq_hi << 32);
    wl->sync[index].refresh_usec = (uint64_t)refresh_nsec/1000;
    wl->sync[index].filled = true;
}