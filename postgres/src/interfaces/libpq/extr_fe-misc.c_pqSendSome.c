#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {char* outBuffer; int outCount; int write_failed; scalar_t__ sock; TYPE_2__ errorMessage; void* write_err_msg; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
#define  EAGAIN 130 
#define  EINTR 129 
#define  EWOULDBLOCK 128 
 int Min (int,int) ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int SOCK_ERRNO ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 scalar_t__ pqIsnonblocking (TYPE_1__*) ; 
 scalar_t__ pqReadData (TYPE_1__*) ; 
 scalar_t__ pqWait (int,int,TYPE_1__*) ; 
 int pqsecure_write (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_2__*) ; 
 void* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pqSendSome(PGconn *conn, int len)
{
	char	   *ptr = conn->outBuffer;
	int			remaining = conn->outCount;
	int			result = 0;

	/*
	 * If we already had a write failure, we will never again try to send data
	 * on that connection.  Even if the kernel would let us, we've probably
	 * lost message boundary sync with the server.  conn->write_failed
	 * therefore persists until the connection is reset, and we just discard
	 * all data presented to be written.
	 */
	if (conn->write_failed)
	{
		/* conn->write_err_msg should be set up already */
		conn->outCount = 0;
		return 0;
	}

	if (conn->sock == PGINVALID_SOCKET)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("connection not open\n"));
		conn->write_failed = true;
		/* Transfer error message to conn->write_err_msg, if possible */
		/* (strdup failure is OK, we'll cope later) */
		conn->write_err_msg = strdup(conn->errorMessage.data);
		resetPQExpBuffer(&conn->errorMessage);
		/* Discard queued data; no chance it'll ever be sent */
		conn->outCount = 0;
		return 0;
	}

	/* while there's still data to send */
	while (len > 0)
	{
		int			sent;

#ifndef WIN32
		sent = pqsecure_write(conn, ptr, len);
#else

		/*
		 * Windows can fail on large sends, per KB article Q201213. The
		 * failure-point appears to be different in different versions of
		 * Windows, but 64k should always be safe.
		 */
		sent = pqsecure_write(conn, ptr, Min(len, 65536));
#endif

		if (sent < 0)
		{
			/* Anything except EAGAIN/EWOULDBLOCK/EINTR is trouble */
			switch (SOCK_ERRNO)
			{
#ifdef EAGAIN
				case EAGAIN:
					break;
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
				case EWOULDBLOCK:
					break;
#endif
				case EINTR:
					continue;

				default:
					/* pqsecure_write set the error message for us */
					conn->write_failed = true;

					/*
					 * Transfer error message to conn->write_err_msg, if
					 * possible (strdup failure is OK, we'll cope later).
					 *
					 * Note: this assumes that pqsecure_write and its children
					 * will overwrite not append to conn->errorMessage.  If
					 * that's ever changed, we could remember the length of
					 * conn->errorMessage at entry to this routine, and then
					 * save and delete just what was appended.
					 */
					conn->write_err_msg = strdup(conn->errorMessage.data);
					resetPQExpBuffer(&conn->errorMessage);

					/* Discard queued data; no chance it'll ever be sent */
					conn->outCount = 0;
					return 0;
			}
		}
		else
		{
			ptr += sent;
			len -= sent;
			remaining -= sent;
		}

		if (len > 0)
		{
			/*
			 * We didn't send it all, wait till we can send more.
			 *
			 * There are scenarios in which we can't send data because the
			 * communications channel is full, but we cannot expect the server
			 * to clear the channel eventually because it's blocked trying to
			 * send data to us.  (This can happen when we are sending a large
			 * amount of COPY data, and the server has generated lots of
			 * NOTICE responses.)  To avoid a deadlock situation, we must be
			 * prepared to accept and buffer incoming data before we try
			 * again.  Furthermore, it is possible that such incoming data
			 * might not arrive until after we've gone to sleep.  Therefore,
			 * we wait for either read ready or write ready.
			 *
			 * In non-blocking mode, we don't wait here directly, but return 1
			 * to indicate that data is still pending.  The caller should wait
			 * for both read and write ready conditions, and call
			 * PQconsumeInput() on read ready, but just in case it doesn't, we
			 * call pqReadData() ourselves before returning.  That's not
			 * enough if the data has not arrived yet, but it's the best we
			 * can do, and works pretty well in practice.  (The documentation
			 * used to say that you only need to wait for write-ready, so
			 * there are still plenty of applications like that out there.)
			 *
			 * Note that errors here don't result in write_failed becoming
			 * set.
			 */
			if (pqReadData(conn) < 0)
			{
				result = -1;	/* error message already set up */
				break;
			}

			if (pqIsnonblocking(conn))
			{
				result = 1;
				break;
			}

			if (pqWait(true, true, conn))
			{
				result = -1;
				break;
			}
		}
	}

	/* shift the remaining contents of the buffer */
	if (remaining > 0)
		memmove(conn->outBuffer, ptr, remaining);
	conn->outCount = remaining;

	return result;
}