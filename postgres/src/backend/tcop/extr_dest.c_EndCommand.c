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
 int /*<<< orphan*/  pq_putmessage (char,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
EndCommand(const char *commandTag, CommandDest dest)
{
	switch (dest)
	{
		case DestRemote:
		case DestRemoteExecute:
		case DestRemoteSimple:

			/*
			 * We assume the commandTag is plain ASCII and therefore requires
			 * no encoding conversion.
			 */
			pq_putmessage('C', commandTag, strlen(commandTag) + 1);
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