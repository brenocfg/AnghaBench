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
typedef  int uint32 ;
struct TYPE_4__ {int outMsgEnd; int outCount; scalar_t__ outMsgStart; int outBuffer; scalar_t__ Pfdebug; } ;
typedef  TYPE_1__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  memcpy (int,int*,int) ; 
 int pg_hton32 (int) ; 
 scalar_t__ pqSendSome (TYPE_1__*,int) ; 

int
pqPutMsgEnd(PGconn *conn)
{
	if (conn->Pfdebug)
		fprintf(conn->Pfdebug, "To backend> Msg complete, length %u\n",
				conn->outMsgEnd - conn->outCount);

	/* Fill in length word if needed */
	if (conn->outMsgStart >= 0)
	{
		uint32		msgLen = conn->outMsgEnd - conn->outMsgStart;

		msgLen = pg_hton32(msgLen);
		memcpy(conn->outBuffer + conn->outMsgStart, &msgLen, 4);
	}

	/* Make message eligible to send */
	conn->outCount = conn->outMsgEnd;

	if (conn->outCount >= 8192)
	{
		int			toSend = conn->outCount - (conn->outCount % 8192);

		if (pqSendSome(conn, toSend) < 0)
			return EOF;
		/* in nonblock mode, don't complain if unable to send it all */
	}

	return 0;
}