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
struct TYPE_3__ {size_t opened; int* fds; } ;
typedef  TYPE_1__ LISTEN_SOCKETS ;

/* Variables and functions */

int listen_sockets_check_is_member(LISTEN_SOCKETS *sockets, int fd) {
    size_t i;
    for(i = 0; i < sockets->opened ;i++)
        if(sockets->fds[i] == fd) return 1;

    return 0;
}