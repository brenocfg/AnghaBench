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
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMMERROR ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int EOF ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  MyProcPort ; 
 int /*<<< orphan*/  PqCommReadingMsg ; 
 unsigned char* PqRecvBuffer ; 
 scalar_t__ PqRecvLength ; 
 scalar_t__ PqRecvPointer ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_socket_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ errno ; 
 int secure_read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  socket_set_nonblocking (int) ; 

int
pq_getbyte_if_available(unsigned char *c)
{
	int			r;

	Assert(PqCommReadingMsg);

	if (PqRecvPointer < PqRecvLength)
	{
		*c = PqRecvBuffer[PqRecvPointer++];
		return 1;
	}

	/* Put the socket into non-blocking mode */
	socket_set_nonblocking(true);

	r = secure_read(MyProcPort, c, 1);
	if (r < 0)
	{
		/*
		 * Ok if no data available without blocking or interrupted (though
		 * EINTR really shouldn't happen with a non-blocking socket). Report
		 * other errors.
		 */
		if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
			r = 0;
		else
		{
			/*
			 * Careful: an ereport() that tries to write to the client would
			 * cause recursion to here, leading to stack overflow and core
			 * dump!  This message must go *only* to the postmaster log.
			 */
			ereport(COMMERROR,
					(errcode_for_socket_access(),
					 errmsg("could not receive data from client: %m")));
			r = EOF;
		}
	}
	else if (r == 0)
	{
		/* EOF detected */
		r = EOF;
	}

	return r;
}