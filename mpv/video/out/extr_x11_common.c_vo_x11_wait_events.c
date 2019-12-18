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
struct vo_x11_state {int /*<<< orphan*/ * wakeup_pipe; int /*<<< orphan*/  event_fd; } ;
struct vo {struct vo_x11_state* x11; } ;
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
typedef  int int64_t ;

/* Variables and functions */
 int MPCLAMP (int,int /*<<< orphan*/ ,int) ; 
 int POLLIN ; 
 int /*<<< orphan*/  mp_flush_wakeup_pipe (int /*<<< orphan*/ ) ; 
 int mp_time_us () ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 

void vo_x11_wait_events(struct vo *vo, int64_t until_time_us)
{
    struct vo_x11_state *x11 = vo->x11;

    struct pollfd fds[2] = {
        { .fd = x11->event_fd, .events = POLLIN },
        { .fd = x11->wakeup_pipe[0], .events = POLLIN },
    };
    int64_t wait_us = until_time_us - mp_time_us();
    int timeout_ms = MPCLAMP((wait_us + 999) / 1000, 0, 10000);

    poll(fds, 2, timeout_ms);

    if (fds[1].revents & POLLIN)
        mp_flush_wakeup_pipe(x11->wakeup_pipe[0]);
}