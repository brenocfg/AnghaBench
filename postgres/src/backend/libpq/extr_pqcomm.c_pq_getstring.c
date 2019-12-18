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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int EOF ; 
 int /*<<< orphan*/  PqCommReadingMsg ; 
 char* PqRecvBuffer ; 
 int PqRecvLength ; 
 int PqRecvPointer ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ pq_recvbuf () ; 
 int /*<<< orphan*/  resetStringInfo (int /*<<< orphan*/ ) ; 

int
pq_getstring(StringInfo s)
{
	int			i;

	Assert(PqCommReadingMsg);

	resetStringInfo(s);

	/* Read until we get the terminating '\0' */
	for (;;)
	{
		while (PqRecvPointer >= PqRecvLength)
		{
			if (pq_recvbuf())	/* If nothing in buffer, then recv some */
				return EOF;		/* Failed to recv data */
		}

		for (i = PqRecvPointer; i < PqRecvLength; i++)
		{
			if (PqRecvBuffer[i] == '\0')
			{
				/* include the '\0' in the copy */
				appendBinaryStringInfo(s, PqRecvBuffer + PqRecvPointer,
									   i - PqRecvPointer + 1);
				PqRecvPointer = i + 1;	/* advance past \0 */
				return 0;
			}
		}

		/* If we're here we haven't got the \0 in the buffer yet. */
		appendBinaryStringInfo(s, PqRecvBuffer + PqRecvPointer,
							   PqRecvLength - PqRecvPointer);
		PqRecvPointer = PqRecvLength;
	}
}