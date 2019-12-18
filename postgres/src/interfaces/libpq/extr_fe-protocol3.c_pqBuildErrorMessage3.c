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
struct TYPE_4__ {char const* errMsg; char* errQuery; scalar_t__ resultStatus; int /*<<< orphan*/  client_encoding; int /*<<< orphan*/ * errFields; } ;
typedef  int /*<<< orphan*/  PQExpBuffer ;
typedef  TYPE_1__ PGresult ;
typedef  scalar_t__ PGVerbosity ;
typedef  scalar_t__ PGContextVisibility ;

/* Variables and functions */
 scalar_t__ PGRES_FATAL_ERROR ; 
 int /*<<< orphan*/  PG_DIAG_COLUMN_NAME ; 
 int /*<<< orphan*/  PG_DIAG_CONSTRAINT_NAME ; 
 int /*<<< orphan*/  PG_DIAG_CONTEXT ; 
 int /*<<< orphan*/  PG_DIAG_DATATYPE_NAME ; 
 int /*<<< orphan*/  PG_DIAG_INTERNAL_POSITION ; 
 int /*<<< orphan*/  PG_DIAG_INTERNAL_QUERY ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_DETAIL ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_HINT ; 
 int /*<<< orphan*/  PG_DIAG_MESSAGE_PRIMARY ; 
 int /*<<< orphan*/  PG_DIAG_SCHEMA_NAME ; 
 int /*<<< orphan*/  PG_DIAG_SEVERITY ; 
 int /*<<< orphan*/  PG_DIAG_SOURCE_FILE ; 
 int /*<<< orphan*/  PG_DIAG_SOURCE_FUNCTION ; 
 int /*<<< orphan*/  PG_DIAG_SOURCE_LINE ; 
 int /*<<< orphan*/  PG_DIAG_SQLSTATE ; 
 int /*<<< orphan*/  PG_DIAG_STATEMENT_POSITION ; 
 int /*<<< orphan*/  PG_DIAG_TABLE_NAME ; 
 scalar_t__ PQERRORS_SQLSTATE ; 
 scalar_t__ PQERRORS_TERSE ; 
 scalar_t__ PQERRORS_VERBOSE ; 
 scalar_t__ PQSHOW_CONTEXT_ALWAYS ; 
 scalar_t__ PQSHOW_CONTEXT_ERRORS ; 
 char* PQresultErrorField (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendPQExpBuffer (int /*<<< orphan*/ ,char const*,char const*,...) ; 
 int /*<<< orphan*/  appendPQExpBufferChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendPQExpBufferStr (int /*<<< orphan*/ ,char const*) ; 
 int atoi (char const*) ; 
 char const* libpq_gettext (char*) ; 
 int /*<<< orphan*/  reportErrorPosition (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

void
pqBuildErrorMessage3(PQExpBuffer msg, const PGresult *res,
					 PGVerbosity verbosity, PGContextVisibility show_context)
{
	const char *val;
	const char *querytext = NULL;
	int			querypos = 0;

	/* If we couldn't allocate a PGresult, just say "out of memory" */
	if (res == NULL)
	{
		appendPQExpBufferStr(msg, libpq_gettext("out of memory\n"));
		return;
	}

	/*
	 * If we don't have any broken-down fields, just return the base message.
	 * This mainly applies if we're given a libpq-generated error result.
	 */
	if (res->errFields == NULL)
	{
		if (res->errMsg && res->errMsg[0])
			appendPQExpBufferStr(msg, res->errMsg);
		else
			appendPQExpBufferStr(msg, libpq_gettext("no error message available\n"));
		return;
	}

	/* Else build error message from relevant fields */
	val = PQresultErrorField(res, PG_DIAG_SEVERITY);
	if (val)
		appendPQExpBuffer(msg, "%s:  ", val);

	if (verbosity == PQERRORS_SQLSTATE)
	{
		/*
		 * If we have a SQLSTATE, print that and nothing else.  If not (which
		 * shouldn't happen for server-generated errors, but might possibly
		 * happen for libpq-generated ones), fall back to TERSE format, as
		 * that seems better than printing nothing at all.
		 */
		val = PQresultErrorField(res, PG_DIAG_SQLSTATE);
		if (val)
		{
			appendPQExpBuffer(msg, "%s\n", val);
			return;
		}
		verbosity = PQERRORS_TERSE;
	}

	if (verbosity == PQERRORS_VERBOSE)
	{
		val = PQresultErrorField(res, PG_DIAG_SQLSTATE);
		if (val)
			appendPQExpBuffer(msg, "%s: ", val);
	}
	val = PQresultErrorField(res, PG_DIAG_MESSAGE_PRIMARY);
	if (val)
		appendPQExpBufferStr(msg, val);
	val = PQresultErrorField(res, PG_DIAG_STATEMENT_POSITION);
	if (val)
	{
		if (verbosity != PQERRORS_TERSE && res->errQuery != NULL)
		{
			/* emit position as a syntax cursor display */
			querytext = res->errQuery;
			querypos = atoi(val);
		}
		else
		{
			/* emit position as text addition to primary message */
			/* translator: %s represents a digit string */
			appendPQExpBuffer(msg, libpq_gettext(" at character %s"),
							  val);
		}
	}
	else
	{
		val = PQresultErrorField(res, PG_DIAG_INTERNAL_POSITION);
		if (val)
		{
			querytext = PQresultErrorField(res, PG_DIAG_INTERNAL_QUERY);
			if (verbosity != PQERRORS_TERSE && querytext != NULL)
			{
				/* emit position as a syntax cursor display */
				querypos = atoi(val);
			}
			else
			{
				/* emit position as text addition to primary message */
				/* translator: %s represents a digit string */
				appendPQExpBuffer(msg, libpq_gettext(" at character %s"),
								  val);
			}
		}
	}
	appendPQExpBufferChar(msg, '\n');
	if (verbosity != PQERRORS_TERSE)
	{
		if (querytext && querypos > 0)
			reportErrorPosition(msg, querytext, querypos,
								res->client_encoding);
		val = PQresultErrorField(res, PG_DIAG_MESSAGE_DETAIL);
		if (val)
			appendPQExpBuffer(msg, libpq_gettext("DETAIL:  %s\n"), val);
		val = PQresultErrorField(res, PG_DIAG_MESSAGE_HINT);
		if (val)
			appendPQExpBuffer(msg, libpq_gettext("HINT:  %s\n"), val);
		val = PQresultErrorField(res, PG_DIAG_INTERNAL_QUERY);
		if (val)
			appendPQExpBuffer(msg, libpq_gettext("QUERY:  %s\n"), val);
		if (show_context == PQSHOW_CONTEXT_ALWAYS ||
			(show_context == PQSHOW_CONTEXT_ERRORS &&
			 res->resultStatus == PGRES_FATAL_ERROR))
		{
			val = PQresultErrorField(res, PG_DIAG_CONTEXT);
			if (val)
				appendPQExpBuffer(msg, libpq_gettext("CONTEXT:  %s\n"),
								  val);
		}
	}
	if (verbosity == PQERRORS_VERBOSE)
	{
		val = PQresultErrorField(res, PG_DIAG_SCHEMA_NAME);
		if (val)
			appendPQExpBuffer(msg,
							  libpq_gettext("SCHEMA NAME:  %s\n"), val);
		val = PQresultErrorField(res, PG_DIAG_TABLE_NAME);
		if (val)
			appendPQExpBuffer(msg,
							  libpq_gettext("TABLE NAME:  %s\n"), val);
		val = PQresultErrorField(res, PG_DIAG_COLUMN_NAME);
		if (val)
			appendPQExpBuffer(msg,
							  libpq_gettext("COLUMN NAME:  %s\n"), val);
		val = PQresultErrorField(res, PG_DIAG_DATATYPE_NAME);
		if (val)
			appendPQExpBuffer(msg,
							  libpq_gettext("DATATYPE NAME:  %s\n"), val);
		val = PQresultErrorField(res, PG_DIAG_CONSTRAINT_NAME);
		if (val)
			appendPQExpBuffer(msg,
							  libpq_gettext("CONSTRAINT NAME:  %s\n"), val);
	}
	if (verbosity == PQERRORS_VERBOSE)
	{
		const char *valf;
		const char *vall;

		valf = PQresultErrorField(res, PG_DIAG_SOURCE_FILE);
		vall = PQresultErrorField(res, PG_DIAG_SOURCE_LINE);
		val = PQresultErrorField(res, PG_DIAG_SOURCE_FUNCTION);
		if (val || valf || vall)
		{
			appendPQExpBufferStr(msg, libpq_gettext("LOCATION:  "));
			if (val)
				appendPQExpBuffer(msg, libpq_gettext("%s, "), val);
			if (valf && vall)	/* unlikely we'd have just one */
				appendPQExpBuffer(msg, libpq_gettext("%s:%s"),
								  valf, vall);
			appendPQExpBufferChar(msg, '\n');
		}
	}
}