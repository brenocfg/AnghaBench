#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {scalar_t__ xactStatus; int /*<<< orphan*/  errorMessage; TYPE_3__* result; } ;
struct TYPE_18__ {int /*<<< orphan*/  noticeRecArg; int /*<<< orphan*/  (* noticeRec ) (int /*<<< orphan*/ ,TYPE_3__*) ;} ;
struct TYPE_20__ {TYPE_1__ noticeHooks; int /*<<< orphan*/  errMsg; int /*<<< orphan*/  resultStatus; } ;
struct TYPE_19__ {char* data; int len; } ;
typedef  TYPE_2__ PQExpBufferData ;
typedef  TYPE_3__ PGresult ;
typedef  TYPE_4__ PGconn ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  PGRES_EMPTY_QUERY ; 
 int /*<<< orphan*/  PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/  PGRES_NONFATAL_ERROR ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_DETAIL ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SEVERITY ; 
 int /*<<< orphan*/  PQExpBufferDataBroken (TYPE_2__) ; 
 scalar_t__ PQTRANS_INERROR ; 
 scalar_t__ PQTRANS_INTRANS ; 
 int /*<<< orphan*/  PQclear (TYPE_3__*) ; 
 TYPE_3__* PQmakeEmptyPGresult (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initPQExpBuffer (TYPE_2__*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  libpq_gettext (char*) ; 
 int /*<<< orphan*/  pqClearAsyncResult (TYPE_4__*) ; 
 scalar_t__ pqGets (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  pqResultStrdup (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  pqSaveMessageField (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printfPQExpBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  termPQExpBuffer (TYPE_2__*) ; 

__attribute__((used)) static int
pqGetErrorNotice2(PGconn *conn, bool isError)
{
	PGresult   *res = NULL;
	PQExpBufferData workBuf;
	char	   *startp;
	char	   *splitp;

	/*
	 * If this is an error message, pre-emptively clear any incomplete query
	 * result we may have.  We'd just throw it away below anyway, and
	 * releasing it before collecting the error might avoid out-of-memory.
	 */
	if (isError)
		pqClearAsyncResult(conn);

	/*
	 * Since the message might be pretty long, we create a temporary
	 * PQExpBuffer rather than using conn->workBuffer.  workBuffer is intended
	 * for stuff that is expected to be short.
	 */
	initPQExpBuffer(&workBuf);
	if (pqGets(&workBuf, conn))
		goto failure;

	/*
	 * Make a PGresult to hold the message.  We temporarily lie about the
	 * result status, so that PQmakeEmptyPGresult doesn't uselessly copy
	 * conn->errorMessage.
	 *
	 * NB: This allocation can fail, if you run out of memory. The rest of the
	 * function handles that gracefully, and we still try to set the error
	 * message as the connection's error message.
	 */
	res = PQmakeEmptyPGresult(conn, PGRES_EMPTY_QUERY);
	if (res)
	{
		res->resultStatus = isError ? PGRES_FATAL_ERROR : PGRES_NONFATAL_ERROR;
		res->errMsg = pqResultStrdup(res, workBuf.data);
	}

	/*
	 * Break the message into fields.  We can't do very much here, but we can
	 * split the severity code off, and remove trailing newlines. Also, we use
	 * the heuristic that the primary message extends only to the first
	 * newline --- anything after that is detail message.  (In some cases it'd
	 * be better classed as hint, but we can hardly be expected to guess that
	 * here.)
	 */
	while (workBuf.len > 0 && workBuf.data[workBuf.len - 1] == '\n')
		workBuf.data[--workBuf.len] = '\0';
	splitp = strstr(workBuf.data, ":  ");
	if (splitp)
	{
		/* what comes before the colon is severity */
		*splitp = '\0';
		pqSaveMessageField(res, PG_DIAG_SEVERITY, workBuf.data);
		startp = splitp + 3;
	}
	else
	{
		/* can't find a colon?  oh well... */
		startp = workBuf.data;
	}
	splitp = strchr(startp, '\n');
	if (splitp)
	{
		/* what comes before the newline is primary message */
		*splitp++ = '\0';
		pqSaveMessageField(res, PG_DIAG_MESSAGE_PRIMARY, startp);
		/* the rest is detail; strip any leading whitespace */
		while (*splitp && isspace((unsigned char) *splitp))
			splitp++;
		pqSaveMessageField(res, PG_DIAG_MESSAGE_DETAIL, splitp);
	}
	else
	{
		/* single-line message, so all primary */
		pqSaveMessageField(res, PG_DIAG_MESSAGE_PRIMARY, startp);
	}

	/*
	 * Either save error as current async result, or just emit the notice.
	 * Also, if it's an error and we were in a transaction block, assume the
	 * server has now gone to error-in-transaction state.
	 */
	if (isError)
	{
		pqClearAsyncResult(conn);	/* redundant, but be safe */
		conn->result = res;
		resetPQExpBuffer(&conn->errorMessage);
		if (res && !PQExpBufferDataBroken(workBuf) && res->errMsg)
			appendPQExpBufferStr(&conn->errorMessage, res->errMsg);
		else
			printfPQExpBuffer(&conn->errorMessage,
							  libpq_gettext("out of memory"));
		if (conn->xactStatus == PQTRANS_INTRANS)
			conn->xactStatus = PQTRANS_INERROR;
	}
	else
	{
		if (res)
		{
			if (res->noticeHooks.noticeRec != NULL)
				res->noticeHooks.noticeRec(res->noticeHooks.noticeRecArg, res);
			PQclear(res);
		}
	}

	termPQExpBuffer(&workBuf);
	return 0;

failure:
	if (res)
		PQclear(res);
	termPQExpBuffer(&workBuf);
	return EOF;
}