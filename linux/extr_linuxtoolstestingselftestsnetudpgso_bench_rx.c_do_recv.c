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
 int bytes ; 
 scalar_t__ cfg_tcp ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  do_flush_tcp (int) ; 
 int /*<<< orphan*/  do_flush_udp (int) ; 
 int /*<<< orphan*/  do_poll (int) ; 
 int do_socket (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 int gettimeofday_ms () ; 
 int /*<<< orphan*/  interrupted ; 
 int packets ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_recv(void)
{
	unsigned long tnow, treport;
	int fd;

	fd = do_socket(cfg_tcp);

	treport = gettimeofday_ms() + 1000;
	do {
		do_poll(fd);

		if (cfg_tcp)
			do_flush_tcp(fd);
		else
			do_flush_udp(fd);

		tnow = gettimeofday_ms();
		if (tnow > treport) {
			if (packets)
				fprintf(stderr,
					"%s rx: %6lu MB/s %8lu calls/s\n",
					cfg_tcp ? "tcp" : "udp",
					bytes >> 20, packets);
			bytes = packets = 0;
			treport = tnow + 1000;
		}

	} while (!interrupted);

	if (close(fd))
		error(1, errno, "close");
}