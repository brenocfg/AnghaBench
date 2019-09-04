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
struct TYPE_3__ {size_t opened; int* fds; int* fds_types; scalar_t__ failed; int /*<<< orphan*/ ** fds_names; } ;
typedef  TYPE_1__ LISTEN_SOCKETS ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  freez (int /*<<< orphan*/ *) ; 

void listen_sockets_close(LISTEN_SOCKETS *sockets) {
    size_t i;
    for(i = 0; i < sockets->opened ;i++) {
        close(sockets->fds[i]);
        sockets->fds[i] = -1;

        freez(sockets->fds_names[i]);
        sockets->fds_names[i] = NULL;

        sockets->fds_types[i] = -1;
    }

    sockets->opened = 0;
    sockets->failed = 0;
}