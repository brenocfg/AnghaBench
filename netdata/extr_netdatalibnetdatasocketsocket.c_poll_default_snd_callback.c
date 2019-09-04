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
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ POLLINFO ;

/* Variables and functions */
 short POLLOUT ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 

int poll_default_snd_callback(POLLINFO *pi, short int *events) {
    *events &= ~POLLOUT;

    info("POLLFD: internal error: poll_default_snd_callback(): nothing to send on socket %d", pi->fd);
    return 0;
}