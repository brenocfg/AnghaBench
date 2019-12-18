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
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ POLLINFO ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 short POLLIN ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int /*<<< orphan*/  info (char*,int,int /*<<< orphan*/ ) ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

int poll_default_rcv_callback(POLLINFO *pi, short int *events) {
    *events |= POLLIN;

    char buffer[1024 + 1];

    ssize_t rc;
    do {
        rc = recv(pi->fd, buffer, 1024, MSG_DONTWAIT);
        if (rc < 0) {
            // read failed
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                error("POLLFD: poll_default_rcv_callback(): recv() failed with %zd.", rc);
                return -1;
            }
        } else if (rc) {
            // data received
            info("POLLFD: internal error: poll_default_rcv_callback() is discarding %zd bytes received on socket %d", rc, pi->fd);
        }
    } while (rc != -1);

    return 0;
}