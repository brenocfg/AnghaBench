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
struct TYPE_3__ {int maxfd; int /*<<< orphan*/  fds; } ;
typedef  TYPE_1__ socket_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int FD_SETSIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
add_socket_to_set(socket_set *sa, int fd, int idx)
{
	if (fd < 0 || fd >= FD_SETSIZE)
	{
		/*
		 * Doing a hard exit here is a bit grotty, but it doesn't seem worth
		 * complicating the API to make it less grotty.
		 */
		fprintf(stderr, "too many client connections for select()\n");
		exit(1);
	}
	FD_SET(fd, &sa->fds);
	if (fd > sa->maxfd)
		sa->maxfd = fd;
}