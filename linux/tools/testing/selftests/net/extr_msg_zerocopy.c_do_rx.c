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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int SOCK_STREAM ; 
 int bytes ; 
 scalar_t__ cfg_runtime_ms ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  do_flush_datagram (int,int) ; 
 int /*<<< orphan*/  do_flush_tcp (int) ; 
 int /*<<< orphan*/  do_poll (int,int /*<<< orphan*/ ) ; 
 int do_setup_rx (int,int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gettimeofday_ms () ; 
 int /*<<< orphan*/  packets ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_rx(int domain, int type, int protocol)
{
	const int cfg_receiver_wait_ms = 400;
	uint64_t tstop;
	int fd;

	fd = do_setup_rx(domain, type, protocol);

	tstop = gettimeofday_ms() + cfg_runtime_ms + cfg_receiver_wait_ms;
	do {
		if (type == SOCK_STREAM)
			do_flush_tcp(fd);
		else
			do_flush_datagram(fd, type);

		do_poll(fd, POLLIN);

	} while (gettimeofday_ms() < tstop);

	if (close(fd))
		error(1, errno, "close");

	fprintf(stderr, "rx=%lu (%lu MB)\n", packets, bytes >> 20);
}