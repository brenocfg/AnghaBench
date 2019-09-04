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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 int /*<<< orphan*/  do_bind (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pair_udp_setfilter (int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_sniffer(void)
{
	struct timeval tv = { .tv_usec = 100 * 1000 };
	int fd;

	fd = socket(PF_PACKET, SOCK_RAW, 0);
	if (fd == -1)
		error(1, errno, "socket p");

	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
		error(1, errno, "setsockopt rcv timeout");

	pair_udp_setfilter(fd);
	do_bind(fd);

	return fd;
}