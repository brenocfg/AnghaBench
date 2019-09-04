#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
struct timespec {long long tv_sec; int tv_nsec; } ;
struct TYPE_6__ {unsigned int vsync_duration; unsigned int skipped_vsyncs; unsigned int last_queue_display_time; } ;
struct TYPE_4__ {unsigned int msc; unsigned int ust; unsigned int sbc; } ;
struct priv {int waiting_for_flip; TYPE_3__ vsync_info; TYPE_1__ vsync; } ;
struct pflip_cb_closure {struct gbm_frame* frame; struct priv* priv; } ;
struct TYPE_5__ {scalar_t__ ust; unsigned int msc; unsigned int sbc; } ;
struct gbm_frame {TYPE_2__ vsync; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 unsigned int const mp_time_us () ; 
 int /*<<< orphan*/  talloc_free (struct pflip_cb_closure*) ; 

__attribute__((used)) static void page_flipped(int fd, unsigned int msc, unsigned int sec,
                         unsigned int usec, void *data)
{
    struct pflip_cb_closure *closure = data;
    struct priv *p = closure->priv;

    // frame->vsync.ust is the timestamp of the pageflip that happened just before this flip was queued
    // frame->vsync.msc is the sequence number of the pageflip that happened just before this flip was queued
    // frame->vsync.sbc is the sequence number for the frame that was just flipped to screen
    struct gbm_frame *frame = closure->frame;

    const bool ready =
        (p->vsync.msc != 0) &&
        (frame->vsync.ust != 0) && (frame->vsync.msc != 0);

    const uint64_t ust = (sec * 1000000LL) + usec;

    const unsigned int msc_since_last_flip = msc - p->vsync.msc;

    p->vsync.ust = ust;
    p->vsync.msc = msc;

    if (ready) {
        // Convert to mp_time
        struct timespec ts;
        if (clock_gettime(CLOCK_MONOTONIC, &ts))
            goto fail;
        const uint64_t now_monotonic = ts.tv_sec * 1000000LL + ts.tv_nsec / 1000;
        const uint64_t ust_mp_time = mp_time_us() - (now_monotonic - p->vsync.ust);

        const uint64_t     ust_since_enqueue = p->vsync.ust - frame->vsync.ust;
        const unsigned int msc_since_enqueue = p->vsync.msc - frame->vsync.msc;
        const unsigned int sbc_since_enqueue = p->vsync.sbc - frame->vsync.sbc;

        p->vsync_info.vsync_duration = ust_since_enqueue / msc_since_enqueue;
        p->vsync_info.skipped_vsyncs = msc_since_last_flip - 1; // Valid iff swap_buffers is called every vsync
        p->vsync_info.last_queue_display_time = ust_mp_time + (sbc_since_enqueue * p->vsync_info.vsync_duration);
    }

fail:
    p->waiting_for_flip = false;
    talloc_free(closure);
}