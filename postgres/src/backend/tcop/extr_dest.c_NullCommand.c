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
typedef  int CommandDest ;

/* Variables and functions */
#define  DestCopyOut 139 
#define  DestDebug 138 
#define  DestIntoRel 137 
#define  DestNone 136 
#define  DestRemote 135 
#define  DestRemoteExecute 134 
#define  DestRemoteSimple 133 
#define  DestSPI 132 
#define  DestSQLFunction 131 
#define  DestTransientRel 130 
#define  DestTupleQueue 129 
#define  DestTuplestore 128 
 int /*<<< orphan*/  FrontendProtocol ; 
 int PG_PROTOCOL_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_putemptymessage (char) ; 
 int /*<<< orphan*/  pq_putmessage (char,char*,int) ; 

void
NullCommand(CommandDest dest)
{
	switch (dest)
	{
		case DestRemote:
		case DestRemoteExecute:
		case DestRemoteSimple:

			/*
			 * tell the fe that we saw an empty query string.  In protocols
			 * before 3.0 this has a useless empty-string message body.
			 */
			if (PG_PROTOCOL_MAJOR(FrontendProtocol) >= 3)
				pq_putemptymessage('I');
			else
				pq_putmessage('I', "", 1);
			break;

		case DestNone:
		case DestDebug:
		case DestSPI:
		case DestTuplestore:
		case DestIntoRel:
		case DestCopyOut:
		case DestSQLFunction:
		case DestTransientRel:
		case DestTupleQueue:
			break;
	}
}