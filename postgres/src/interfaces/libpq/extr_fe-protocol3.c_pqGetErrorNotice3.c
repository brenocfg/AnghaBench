#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  errorMessage; TYPE_3__* result; int /*<<< orphan*/  show_context; int /*<<< orphan*/  verbosity; void* last_query; int /*<<< orphan*/  last_sqlstate; } ;
struct TYPE_22__ {int /*<<< orphan*/  noticeRecArg; int /*<<< orphan*/  (* noticeRec ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_24__ {TYPE_1__ noticeHooks; void* errMsg; void* errQuery; int /*<<< orphan*/  resultStatus; } ;
struct TYPE_23__ {void* data; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_3__ PGresult ;
typedef  TYPE_4__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  PGRES_EMPTY_QUERY ; 
 int /*<<< orphan*/  PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/  PGRES_NONFATAL_ERROR ; 
 char PG_DIAG_SQLSTATE ; 
 char PG_DIAG_STATEMENT_POSITION ; 
 scalar_t__ PQExpBufferDataBroken (TYPE_2__) ; 
 int /*<<< orphan*/  PQclear (TYPE_3__*) ; 
 TYPE_3__* PQmakeEmptyPGresult (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pqBuildErrorMessage3 (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pqClearAsyncResult (TYPE_4__*) ; 
 scalar_t__ pqGetc (char*,TYPE_4__*) ; 
 scalar_t__ pqGets (TYPE_2__*,TYPE_4__*) ; 
 void* pqResultStrdup (TYPE_3__*,void*) ; 
 int /*<<< orphan*/  pqSaveMessageField (TYPE_3__*,char,void*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

int
pqGetErrorNotice3(PGconn *conn, bool isError)
{
	PGresult   *res = NULL;
	bool		have_position = false;
	PQExpBufferData workBuf;
	char		id;

	/*
	 * If this is an error message, pre-emptively clear any incomplete query
	 * result we may have.  We'd just throw it away below anyway, and
	 * releasing it before collecting the error might avoid out-of-memory.
	 */
	if (isError)
		pqClearAsyncResult(conn);

	/*
	 * Since the fields might be pretty long, we create a temporary
	 * PQExpBuffer rather than using conn->workBuffer.  workBuffer is intended
	 * for stuff that is expected to be short.  We shouldn't use
	 * conn->errorMessage either, since this might be only a notice.
	 */
	initPQExpBuffer(&workBuf);

	/*
	 * Make a PGresult to hold the accumulated fields.  We temporarily lie
	 * about the result status, so that PQmakeEmptyPGresult doesn't uselessly
	 * copy conn->errorMessage.
	 *
	 * NB: This allocation can fail, if you run out of memory. The rest of the
	 * function handles that gracefully, and we still try to set the error
	 * message as the connection's error message.
	 */
	res = PQmakeEmptyPGresult(conn, PGRES_EMPTY_QUERY);
	if (res)
		res->resultStatus = isError ? PGRES_FATAL_ERROR : PGRES_NONFATAL_ERROR;

	/*
	 * Read the fields and save into res.
	 *
	 * While at it, save the SQLSTATE in conn->last_sqlstate, and note whether
	 * we saw a PG_DIAG_STATEMENT_POSITION field.
	 */
	for (;;)
	{
		if (pqGetc(&id, conn))
			goto fail;
		if (id == '\0')
			break;				/* terminator found */
		if (pqGets(&workBuf, conn))
			goto fail;
		pqSaveMessageField(res, id, workBuf.data);
		if (id == PG_DIAG_SQLSTATE)
			strlcpy(conn->last_sqlstate, workBuf.data,
					sizeof(conn->last_sqlstate));
		else if (id == PG_DIAG_STATEMENT_POSITION)
			have_position = true;
	}

	/*
	 * Save the active query text, if any, into res as well; but only if we
	 * might need it for an error cursor display, which is only true if there
	 * is a PG_DIAG_STATEMENT_POSITION field.
	 */
	if (have_position && conn->last_query && res)
		res->errQuery = pqResultStrdup(res, conn->last_query);

	/*
	 * Now build the "overall" error message for PQresultErrorMessage.
	 */
	resetPQExpBuffer(&workBuf);
	pqBuildErrorMessage3(&workBuf, res, conn->verbosity, conn->show_context);

	/*
	 * Either save error as current async result, or just emit the notice.
	 */
	if (isError)
	{
		if (res)
			res->errMsg = pqResultStrdup(res, workBuf.data);
		pqClearAsyncResult(conn);	/* redundant, but be safe */
		conn->result = res;
		if (PQExpBufferDataBroken(workBuf))
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("out of memory"));
		else
			appendPQExpBufferStr(&conn->errorMessage, workBuf.data);
	}
	else
	{
		/* if we couldn't allocate the result set, just discard the NOTICE */
		if (res)
		{
			/* We can cheat a little here and not copy the message. */
			res->errMsg = workBuf.data;
			if (res->noticeHooks.noticeRec != NULL)
				res->noticeHooks.noticeRec(res->noticeHooks.noticeRecArg, res);
			PQclear(res);
		}
	}

	termPQExpBuffer(&workBuf);
	return 0;

fail:
	PQclear(res);
	termPQExpBuffer(&workBuf);
	return EOF;
}