#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_1__ Port ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  MyLatch ; 
 scalar_t__ PqGSSRecvBuffer ; 
 scalar_t__ PqGSSRecvLength ; 
 int /*<<< orphan*/  WAIT_EVENT_GSS_OPEN_SERVER ; 
 int WL_EXIT_ON_PM_DEATH ; 
 int WL_SOCKET_READABLE ; 
 int /*<<< orphan*/  WaitLatchOrSocket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ secure_raw_read (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ssize_t
read_or_wait(Port *port, ssize_t len)
{
	ssize_t		ret;

	/*
	 * Keep going until we either read in everything we were asked to, or we
	 * error out.
	 */
	while (PqGSSRecvLength != len)
	{
		ret = secure_raw_read(port, PqGSSRecvBuffer + PqGSSRecvLength, len - PqGSSRecvLength);

		/*
		 * If we got back an error and it wasn't just EWOULDBLOCK/EAGAIN, then
		 * give up.
		 */
		if (ret < 0 && !(errno == EWOULDBLOCK || errno == EAGAIN))
			return -1;

		/*
		 * Ok, we got back either a positive value, zero, or a negative result
		 * but EWOULDBLOCK or EAGAIN was set.
		 *
		 * If it was zero or negative, then we try to wait on the socket to be
		 * readable again.
		 */
		if (ret <= 0)
		{
			/*
			 * If we got back less than zero, indicating an error, and that
			 * wasn't just a EWOULDBLOCK/EAGAIN, then give up.
			 */
			if (ret < 0 && !(errno == EWOULDBLOCK || errno == EAGAIN))
				return -1;

			/*
			 * We got back either zero, or -1 with EWOULDBLOCK/EAGAIN, so wait
			 * on socket to be readable again.
			 */
			WaitLatchOrSocket(MyLatch,
							  WL_SOCKET_READABLE | WL_EXIT_ON_PM_DEATH,
							  port->sock, 0, WAIT_EVENT_GSS_OPEN_SERVER);

			/*
			 * If we got back zero bytes, and then waited on the socket to be
			 * readable and got back zero bytes on a second read, then this is
			 * EOF and the client hung up on us.
			 *
			 * If we did get data here, then we can just fall through and
			 * handle it just as if we got data the first time.
			 *
			 * Otherwise loop back to the top and try again.
			 */
			if (ret == 0)
			{
				ret = secure_raw_read(port, PqGSSRecvBuffer + PqGSSRecvLength, len - PqGSSRecvLength);
				if (ret == 0)
					return -1;
			}
			else
				continue;
		}

		PqGSSRecvLength += ret;
	}

	return len;
}