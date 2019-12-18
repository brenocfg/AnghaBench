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
struct wl_display {int dummy; } ;
struct vo_wayland_state {int display_fd; int* wakeup_pipe; struct wl_display* display; } ;
struct vo {int /*<<< orphan*/  input_ctx; struct vo_wayland_state* wl; } ;
struct pollfd {int fd; int events; int revents; } ;
typedef  int int64_t ;

/* Variables and functions */
 int MPCLAMP (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MP_FATAL (struct vo_wayland_state*,char*) ; 
 int /*<<< orphan*/  MP_KEY_CLOSE_WIN ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLNVAL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  mp_flush_wakeup_pipe (int) ; 
 int /*<<< orphan*/  mp_input_put_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_time_us () ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  wl_display_dispatch (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_dispatch_pending (struct wl_display*) ; 
 int /*<<< orphan*/  wl_display_flush (struct wl_display*) ; 

void vo_wayland_wait_events(struct vo *vo, int64_t until_time_us)
{
    struct vo_wayland_state *wl = vo->wl;
    struct wl_display *display = wl->display;

    if (wl->display_fd == -1)
        return;

    struct pollfd fds[2] = {
        {.fd = wl->display_fd,     .events = POLLIN },
        {.fd = wl->wakeup_pipe[0], .events = POLLIN },
    };

    int64_t wait_us = until_time_us - mp_time_us();
    int timeout_ms = MPCLAMP((wait_us + 999) / 1000, 0, 10000);

    wl_display_dispatch_pending(display);
    wl_display_flush(display);

    poll(fds, 2, timeout_ms);

    if (fds[0].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        MP_FATAL(wl, "Error occurred on the display fd, closing\n");
        close(wl->display_fd);
        wl->display_fd = -1;
        mp_input_put_key(vo->input_ctx, MP_KEY_CLOSE_WIN);
    }

    if (fds[0].revents & POLLIN)
        wl_display_dispatch(display);

    if (fds[1].revents & POLLIN)
        mp_flush_wakeup_pipe(wl->wakeup_pipe[0]);
}