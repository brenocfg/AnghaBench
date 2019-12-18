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
struct vo_wayland_state {int timeout_count; int hidden; TYPE_1__* current_output; scalar_t__ frame_wait; int /*<<< orphan*/  display; int /*<<< orphan*/  display_fd; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {int refresh_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ mp_time_us () ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  wl_display_dispatch_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ wl_display_prepare_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_read_events (int /*<<< orphan*/ ) ; 

void vo_wayland_wait_frame(struct vo_wayland_state *wl, int frame_offset)
{
    struct pollfd fds[1] = {
        {.fd = wl->display_fd,     .events = POLLIN },
    };

    double vblank_time = 1e6 / wl->current_output->refresh_rate;
    int64_t finish_time = mp_time_us() + vblank_time + (int64_t)frame_offset;

    while (wl->frame_wait && finish_time > mp_time_us()) {

        while (wl_display_prepare_read(wl->display) != 0)
            wl_display_dispatch_pending(wl->display);
        wl_display_flush(wl->display);

        int poll_time = (finish_time - mp_time_us()) / 1000;
        if (poll_time < 0) {
            poll_time = 0;
        }

        poll(fds, 1, poll_time);

        wl_display_read_events(wl->display);
        wl_display_dispatch_pending(wl->display);
    }

    if (wl->frame_wait) {
        wl->timeout_count += 1;
    } else {
        wl->timeout_count = 0;
        wl->hidden = false;
    }
    
    if (wl->timeout_count > wl->current_output->refresh_rate)
        wl->hidden = true;
}