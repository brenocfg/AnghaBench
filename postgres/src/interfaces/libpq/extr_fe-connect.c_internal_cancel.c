#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sebuf ;
typedef  scalar_t__ pgsocket ;
typedef  int /*<<< orphan*/  crp ;
struct TYPE_7__ {void* cancelAuthCode; void* backendPID; scalar_t__ cancelRequestCode; } ;
struct TYPE_5__ {int /*<<< orphan*/  ss_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  salen; TYPE_1__ addr; } ;
typedef  TYPE_2__ SockAddr ;
typedef  scalar_t__ MsgType ;
typedef  TYPE_3__ CancelRequestPacket ;

/* Variables and functions */
 int CANCEL_REQUEST_CODE ; 
 int EINTR ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int PG_STRERROR_R_BUFLEN ; 
 int SOCK_ERRNO ; 
 int /*<<< orphan*/  SOCK_ERRNO_SET (int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOCK_STRERROR (int,char*,int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ connect (scalar_t__,struct sockaddr*,int /*<<< orphan*/ ) ; 
 void* pg_hton32 (int) ; 
 scalar_t__ recv (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int send (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
internal_cancel(SockAddr *raddr, int be_pid, int be_key,
				char *errbuf, int errbufsize)
{
	int			save_errno = SOCK_ERRNO;
	pgsocket	tmpsock = PGINVALID_SOCKET;
	char		sebuf[PG_STRERROR_R_BUFLEN];
	int			maxlen;
	struct
	{
		uint32		packetlen;
		CancelRequestPacket cp;
	}			crp;

	/*
	 * We need to open a temporary connection to the postmaster. Do this with
	 * only kernel calls.
	 */
	if ((tmpsock = socket(raddr->addr.ss_family, SOCK_STREAM, 0)) == PGINVALID_SOCKET)
	{
		strlcpy(errbuf, "PQcancel() -- socket() failed: ", errbufsize);
		goto cancel_errReturn;
	}
retry3:
	if (connect(tmpsock, (struct sockaddr *) &raddr->addr,
				raddr->salen) < 0)
	{
		if (SOCK_ERRNO == EINTR)
			/* Interrupted system call - we'll just try again */
			goto retry3;
		strlcpy(errbuf, "PQcancel() -- connect() failed: ", errbufsize);
		goto cancel_errReturn;
	}

	/*
	 * We needn't set nonblocking I/O or NODELAY options here.
	 */

	/* Create and send the cancel request packet. */

	crp.packetlen = pg_hton32((uint32) sizeof(crp));
	crp.cp.cancelRequestCode = (MsgType) pg_hton32(CANCEL_REQUEST_CODE);
	crp.cp.backendPID = pg_hton32(be_pid);
	crp.cp.cancelAuthCode = pg_hton32(be_key);

retry4:
	if (send(tmpsock, (char *) &crp, sizeof(crp), 0) != (int) sizeof(crp))
	{
		if (SOCK_ERRNO == EINTR)
			/* Interrupted system call - we'll just try again */
			goto retry4;
		strlcpy(errbuf, "PQcancel() -- send() failed: ", errbufsize);
		goto cancel_errReturn;
	}

	/*
	 * Wait for the postmaster to close the connection, which indicates that
	 * it's processed the request.  Without this delay, we might issue another
	 * command only to find that our cancel zaps that command instead of the
	 * one we thought we were canceling.  Note we don't actually expect this
	 * read to obtain any data, we are just waiting for EOF to be signaled.
	 */
retry5:
	if (recv(tmpsock, (char *) &crp, 1, 0) < 0)
	{
		if (SOCK_ERRNO == EINTR)
			/* Interrupted system call - we'll just try again */
			goto retry5;
		/* we ignore other error conditions */
	}

	/* All done */
	closesocket(tmpsock);
	SOCK_ERRNO_SET(save_errno);
	return true;

cancel_errReturn:

	/*
	 * Make sure we don't overflow the error buffer. Leave space for the \n at
	 * the end, and for the terminating zero.
	 */
	maxlen = errbufsize - strlen(errbuf) - 2;
	if (maxlen >= 0)
	{
		strncat(errbuf, SOCK_STRERROR(SOCK_ERRNO, sebuf, sizeof(sebuf)),
				maxlen);
		strcat(errbuf, "\n");
	}
	if (tmpsock != PGINVALID_SOCKET)
		closesocket(tmpsock);
	SOCK_ERRNO_SET(save_errno);
	return false;
}