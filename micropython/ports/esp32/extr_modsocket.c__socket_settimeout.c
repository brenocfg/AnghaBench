#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  timeout ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int retries; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ socket_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int SOCKET_POLL_US ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  SO_SNDTIMEO ; 
 int UINT64_MAX ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  lwip_fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwip_setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int) ; 

void _socket_settimeout(socket_obj_t *sock, uint64_t timeout_ms) {
    // Rather than waiting for the entire timeout specified, we wait sock->retries times
    // for SOCKET_POLL_US each, checking for a MicroPython interrupt between timeouts.
    // with SOCKET_POLL_MS == 100ms, sock->retries allows for timeouts up to 13 years.
    // if timeout_ms == UINT64_MAX, wait forever.
    sock->retries = (timeout_ms == UINT64_MAX) ? UINT_MAX : timeout_ms * 1000 / SOCKET_POLL_US;

    struct timeval timeout = {
        .tv_sec = 0,
        .tv_usec = timeout_ms ? SOCKET_POLL_US : 0
    };
    lwip_setsockopt(sock->fd, SOL_SOCKET, SO_SNDTIMEO, (const void *)&timeout, sizeof(timeout));
    lwip_setsockopt(sock->fd, SOL_SOCKET, SO_RCVTIMEO, (const void *)&timeout, sizeof(timeout));
    lwip_fcntl(sock->fd, F_SETFL, timeout_ms ? 0 : O_NONBLOCK);
}