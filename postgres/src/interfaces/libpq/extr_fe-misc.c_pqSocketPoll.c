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
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; scalar_t__ revents; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  POLLERR ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  POLLOUT ; 
 int poll (struct pollfd*,int,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pqSocketPoll(int sock, int forRead, int forWrite, time_t end_time)
{
	/* We use poll(2) if available, otherwise select(2) */
#ifdef HAVE_POLL
	struct pollfd input_fd;
	int			timeout_ms;

	if (!forRead && !forWrite)
		return 0;

	input_fd.fd = sock;
	input_fd.events = POLLERR;
	input_fd.revents = 0;

	if (forRead)
		input_fd.events |= POLLIN;
	if (forWrite)
		input_fd.events |= POLLOUT;

	/* Compute appropriate timeout interval */
	if (end_time == ((time_t) -1))
		timeout_ms = -1;
	else
	{
		time_t		now = time(NULL);

		if (end_time > now)
			timeout_ms = (end_time - now) * 1000;
		else
			timeout_ms = 0;
	}

	return poll(&input_fd, 1, timeout_ms);
#else							/* !HAVE_POLL */

	fd_set		input_mask;
	fd_set		output_mask;
	fd_set		except_mask;
	struct timeval timeout;
	struct timeval *ptr_timeout;

	if (!forRead && !forWrite)
		return 0;

	FD_ZERO(&input_mask);
	FD_ZERO(&output_mask);
	FD_ZERO(&except_mask);
	if (forRead)
		FD_SET(sock, &input_mask);

	if (forWrite)
		FD_SET(sock, &output_mask);
	FD_SET(sock, &except_mask);

	/* Compute appropriate timeout interval */
	if (end_time == ((time_t) -1))
		ptr_timeout = NULL;
	else
	{
		time_t		now = time(NULL);

		if (end_time > now)
			timeout.tv_sec = end_time - now;
		else
			timeout.tv_sec = 0;
		timeout.tv_usec = 0;
		ptr_timeout = &timeout;
	}

	return select(sock + 1, &input_mask, &output_mask,
				  &except_mask, ptr_timeout);
#endif							/* HAVE_POLL */
}