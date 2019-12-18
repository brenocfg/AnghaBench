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

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int SD_LISTEN_FDS_START ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  lwan_status_critical (char*) ; 
 int /*<<< orphan*/  sd_is_socket_inet (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int set_socket_flags (int) ; 

__attribute__((used)) static int setup_socket_from_systemd(void)
{
    int fd = SD_LISTEN_FDS_START;

    if (!sd_is_socket_inet(fd, AF_UNSPEC, SOCK_STREAM, 1, 0))
        lwan_status_critical("Passed file descriptor is not a "
                             "listening TCP socket");

    return set_socket_flags(fd);
}