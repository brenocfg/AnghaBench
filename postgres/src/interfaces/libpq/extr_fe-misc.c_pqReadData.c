#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ sock; int inStart; int inEnd; scalar_t__ inBuffer; int inCursor; int inBufSize; int /*<<< orphan*/  status; int /*<<< orphan*/  errorMessage; scalar_t__ ssl_in_use; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECTION_BAD ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ ECONNRESET ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ PGINVALID_SOCKET ; 
 scalar_t__ SOCK_ERRNO ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ pqCheckInBufferSpace (size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  pqDropConnection (TYPE_1__*,int) ; 
 int pqReadReady (TYPE_1__*) ; 
 int pqsecure_read (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
pqReadData(PGconn *conn)
{
	int			someread = 0;
	int			nread;

	if (conn->sock == PGINVALID_SOCKET)
	{
		printfPQExpBuffer(&conn->errorMessage,
						  libpq_gettext("connection not open\n"));
		return -1;
	}

	/* Left-justify any data in the buffer to make room */
	if (conn->inStart < conn->inEnd)
	{
		if (conn->inStart > 0)
		{
			memmove(conn->inBuffer, conn->inBuffer + conn->inStart,
					conn->inEnd - conn->inStart);
			conn->inEnd -= conn->inStart;
			conn->inCursor -= conn->inStart;
			conn->inStart = 0;
		}
	}
	else
	{
		/* buffer is logically empty, reset it */
		conn->inStart = conn->inCursor = conn->inEnd = 0;
	}

	/*
	 * If the buffer is fairly full, enlarge it. We need to be able to enlarge
	 * the buffer in case a single message exceeds the initial buffer size. We
	 * enlarge before filling the buffer entirely so as to avoid asking the
	 * kernel for a partial packet. The magic constant here should be large
	 * enough for a TCP packet or Unix pipe bufferload.  8K is the usual pipe
	 * buffer size, so...
	 */
	if (conn->inBufSize - conn->inEnd < 8192)
	{
		if (pqCheckInBufferSpace(conn->inEnd + (size_t) 8192, conn))
		{
			/*
			 * We don't insist that the enlarge worked, but we need some room
			 */
			if (conn->inBufSize - conn->inEnd < 100)
				return -1;		/* errorMessage already set */
		}
	}

	/* OK, try to read some data */
retry3:
	nread = pqsecure_read(conn, conn->inBuffer + conn->inEnd,
						  conn->inBufSize - conn->inEnd);
	if (nread < 0)
	{
		if (SOCK_ERRNO == EINTR)
			goto retry3;
		/* Some systems return EAGAIN/EWOULDBLOCK for no data */
#ifdef EAGAIN
		if (SOCK_ERRNO == EAGAIN)
			return someread;
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
		if (SOCK_ERRNO == EWOULDBLOCK)
			return someread;
#endif
		/* We might get ECONNRESET here if using TCP and backend died */
#ifdef ECONNRESET
		if (SOCK_ERRNO == ECONNRESET)
			goto definitelyFailed;
#endif
		/* pqsecure_read set the error message for us */
		return -1;
	}
	if (nread > 0)
	{
		conn->inEnd += nread;

		/*
		 * Hack to deal with the fact that some kernels will only give us back
		 * 1 packet per recv() call, even if we asked for more and there is
		 * more available.  If it looks like we are reading a long message,
		 * loop back to recv() again immediately, until we run out of data or
		 * buffer space.  Without this, the block-and-restart behavior of
		 * libpq's higher levels leads to O(N^2) performance on long messages.
		 *
		 * Since we left-justified the data above, conn->inEnd gives the
		 * amount of data already read in the current message.  We consider
		 * the message "long" once we have acquired 32k ...
		 */
		if (conn->inEnd > 32768 &&
			(conn->inBufSize - conn->inEnd) >= 8192)
		{
			someread = 1;
			goto retry3;
		}
		return 1;
	}

	if (someread)
		return 1;				/* got a zero read after successful tries */

	/*
	 * A return value of 0 could mean just that no data is now available, or
	 * it could mean EOF --- that is, the server has closed the connection.
	 * Since we have the socket in nonblock mode, the only way to tell the
	 * difference is to see if select() is saying that the file is ready.
	 * Grumble.  Fortunately, we don't expect this path to be taken much,
	 * since in normal practice we should not be trying to read data unless
	 * the file selected for reading already.
	 *
	 * In SSL mode it's even worse: SSL_read() could say WANT_READ and then
	 * data could arrive before we make the pqReadReady() test, but the second
	 * SSL_read() could still say WANT_READ because the data received was not
	 * a complete SSL record.  So we must play dumb and assume there is more
	 * data, relying on the SSL layer to detect true EOF.
	 */

#ifdef USE_SSL
	if (conn->ssl_in_use)
		return 0;
#endif

	switch (pqReadReady(conn))
	{
		case 0:
			/* definitely no data available */
			return 0;
		case 1:
			/* ready for read */
			break;
		default:
			/* we override pqReadReady's message with something more useful */
			goto definitelyEOF;
	}

	/*
	 * Still not sure that it's EOF, because some data could have just
	 * arrived.
	 */
retry4:
	nread = pqsecure_read(conn, conn->inBuffer + conn->inEnd,
						  conn->inBufSize - conn->inEnd);
	if (nread < 0)
	{
		if (SOCK_ERRNO == EINTR)
			goto retry4;
		/* Some systems return EAGAIN/EWOULDBLOCK for no data */
#ifdef EAGAIN
		if (SOCK_ERRNO == EAGAIN)
			return 0;
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
		if (SOCK_ERRNO == EWOULDBLOCK)
			return 0;
#endif
		/* We might get ECONNRESET here if using TCP and backend died */
#ifdef ECONNRESET
		if (SOCK_ERRNO == ECONNRESET)
			goto definitelyFailed;
#endif
		/* pqsecure_read set the error message for us */
		return -1;
	}
	if (nread > 0)
	{
		conn->inEnd += nread;
		return 1;
	}

	/*
	 * OK, we are getting a zero read even though select() says ready. This
	 * means the connection has been closed.  Cope.
	 */
definitelyEOF:
	printfPQExpBuffer(&conn->errorMessage,
					  libpq_gettext(
									"server closed the connection unexpectedly\n"
									"\tThis probably means the server terminated abnormally\n"
									"\tbefore or while processing the request.\n"));

	/* Come here if lower-level code already set a suitable errorMessage */
definitelyFailed:
	/* Do *not* drop any already-read data; caller still wants it */
	pqDropConnection(conn, false);
	conn->status = CONNECTION_BAD;	/* No more connection to backend */
	return -1;
}