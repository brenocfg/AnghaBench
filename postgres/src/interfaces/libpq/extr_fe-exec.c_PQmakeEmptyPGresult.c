#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/ * noticeProcArg; int /*<<< orphan*/ * noticeProc; int /*<<< orphan*/ * noticeRecArg; int /*<<< orphan*/ * noticeRec; } ;
struct TYPE_12__ {scalar_t__ nEvents; int /*<<< orphan*/  events; TYPE_1__ errorMessage; int /*<<< orphan*/  client_encoding; TYPE_2__ noticeHooks; } ;
struct TYPE_11__ {int resultStatus; char* cmdStatus; scalar_t__ nEvents; char* null_field; int memorySize; int /*<<< orphan*/  client_encoding; TYPE_2__ noticeHooks; int /*<<< orphan*/ * events; scalar_t__ spaceLeft; scalar_t__ curOffset; int /*<<< orphan*/ * curBlock; int /*<<< orphan*/ * errQuery; int /*<<< orphan*/ * errFields; int /*<<< orphan*/ * errMsg; scalar_t__ binary; int /*<<< orphan*/ * paramDescs; scalar_t__ numParameters; scalar_t__ tupArrSize; int /*<<< orphan*/ * tuples; int /*<<< orphan*/ * attDescs; scalar_t__ numAttributes; scalar_t__ ntups; } ;
typedef  TYPE_3__ PGresult ;
typedef  TYPE_4__ PGconn ;
typedef  int ExecStatusType ;

/* Variables and functions */
#define  PGRES_COMMAND_OK 134 
#define  PGRES_COPY_BOTH 133 
#define  PGRES_COPY_IN 132 
#define  PGRES_COPY_OUT 131 
#define  PGRES_EMPTY_QUERY 130 
#define  PGRES_SINGLE_TUPLE 129 
#define  PGRES_TUPLES_OK 128 
 int /*<<< orphan*/  PG_SQL_ASCII ; 
 int /*<<< orphan*/  PQclear (TYPE_3__*) ; 
 int /*<<< orphan*/ * dupEvents (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pqSetResultError (TYPE_3__*,int /*<<< orphan*/ ) ; 

PGresult *
PQmakeEmptyPGresult(PGconn *conn, ExecStatusType status)
{
	PGresult   *result;

	result = (PGresult *) malloc(sizeof(PGresult));
	if (!result)
		return NULL;

	result->ntups = 0;
	result->numAttributes = 0;
	result->attDescs = NULL;
	result->tuples = NULL;
	result->tupArrSize = 0;
	result->numParameters = 0;
	result->paramDescs = NULL;
	result->resultStatus = status;
	result->cmdStatus[0] = '\0';
	result->binary = 0;
	result->events = NULL;
	result->nEvents = 0;
	result->errMsg = NULL;
	result->errFields = NULL;
	result->errQuery = NULL;
	result->null_field[0] = '\0';
	result->curBlock = NULL;
	result->curOffset = 0;
	result->spaceLeft = 0;
	result->memorySize = sizeof(PGresult);

	if (conn)
	{
		/* copy connection data we might need for operations on PGresult */
		result->noticeHooks = conn->noticeHooks;
		result->client_encoding = conn->client_encoding;

		/* consider copying conn's errorMessage */
		switch (status)
		{
			case PGRES_EMPTY_QUERY:
			case PGRES_COMMAND_OK:
			case PGRES_TUPLES_OK:
			case PGRES_COPY_OUT:
			case PGRES_COPY_IN:
			case PGRES_COPY_BOTH:
			case PGRES_SINGLE_TUPLE:
				/* non-error cases */
				break;
			default:
				pqSetResultError(result, conn->errorMessage.data);
				break;
		}

		/* copy events last; result must be valid if we need to PQclear */
		if (conn->nEvents > 0)
		{
			result->events = dupEvents(conn->events, conn->nEvents,
									   &result->memorySize);
			if (!result->events)
			{
				PQclear(result);
				return NULL;
			}
			result->nEvents = conn->nEvents;
		}
	}
	else
	{
		/* defaults... */
		result->noticeHooks.noticeRec = NULL;
		result->noticeHooks.noticeRecArg = NULL;
		result->noticeHooks.noticeProc = NULL;
		result->noticeHooks.noticeProcArg = NULL;
		result->client_encoding = PG_SQL_ASCII;
	}

	return result;
}