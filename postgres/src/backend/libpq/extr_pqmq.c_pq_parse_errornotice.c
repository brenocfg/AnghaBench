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
struct TYPE_4__ {void* funcname; void* lineno; void* filename; void* constraint_name; void* datatype_name; void* column_name; void* table_name; void* schema_name; void* context; void* internalquery; void* internalpos; void* cursorpos; void* hint; void* detail; void* message; int /*<<< orphan*/  sqlerrcode; void* elevel; int /*<<< orphan*/  assoc_context; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  TYPE_1__ ErrorData ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 void* DEBUG1 ; 
 void* ERROR ; 
 void* FATAL ; 
 void* INFO ; 
 void* LOG ; 
 int /*<<< orphan*/  MAKE_SQLSTATE (char const,char const,char const,char const,char const) ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 void* NOTICE ; 
 void* PANIC ; 
#define  PG_DIAG_COLUMN_NAME 145 
#define  PG_DIAG_CONSTRAINT_NAME 144 
#define  PG_DIAG_CONTEXT 143 
#define  PG_DIAG_DATATYPE_NAME 142 
#define  PG_DIAG_INTERNAL_POSITION 141 
#define  PG_DIAG_INTERNAL_QUERY 140 
#define  PG_DIAG_MESSAGE_DETAIL 139 
#define  PG_DIAG_MESSAGE_HINT 138 
#define  PG_DIAG_MESSAGE_PRIMARY 137 
#define  PG_DIAG_SCHEMA_NAME 136 
#define  PG_DIAG_SEVERITY 135 
#define  PG_DIAG_SEVERITY_NONLOCALIZED 134 
#define  PG_DIAG_SOURCE_FILE 133 
#define  PG_DIAG_SOURCE_FUNCTION 132 
#define  PG_DIAG_SOURCE_LINE 131 
#define  PG_DIAG_SQLSTATE 130 
#define  PG_DIAG_STATEMENT_POSITION 129 
#define  PG_DIAG_TABLE_NAME 128 
 void* WARNING ; 
 int /*<<< orphan*/  elog (void*,char*,...) ; 
 void* pg_strtoint32 (char const*) ; 
 char pq_getmsgbyte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_getmsgend (int /*<<< orphan*/ ) ; 
 char* pq_getmsgrawstring (int /*<<< orphan*/ ) ; 
 void* pstrdup (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 

void
pq_parse_errornotice(StringInfo msg, ErrorData *edata)
{
	/* Initialize edata with reasonable defaults. */
	MemSet(edata, 0, sizeof(ErrorData));
	edata->elevel = ERROR;
	edata->assoc_context = CurrentMemoryContext;

	/* Loop over fields and extract each one. */
	for (;;)
	{
		char		code = pq_getmsgbyte(msg);
		const char *value;

		if (code == '\0')
		{
			pq_getmsgend(msg);
			break;
		}
		value = pq_getmsgrawstring(msg);

		switch (code)
		{
			case PG_DIAG_SEVERITY:
				/* ignore, trusting we'll get a nonlocalized version */
				break;
			case PG_DIAG_SEVERITY_NONLOCALIZED:
				if (strcmp(value, "DEBUG") == 0)
				{
					/*
					 * We can't reconstruct the exact DEBUG level, but
					 * presumably it was >= client_min_messages, so select
					 * DEBUG1 to ensure we'll pass it on to the client.
					 */
					edata->elevel = DEBUG1;
				}
				else if (strcmp(value, "LOG") == 0)
				{
					/*
					 * It can't be LOG_SERVER_ONLY, or the worker wouldn't
					 * have sent it to us; so LOG is the correct value.
					 */
					edata->elevel = LOG;
				}
				else if (strcmp(value, "INFO") == 0)
					edata->elevel = INFO;
				else if (strcmp(value, "NOTICE") == 0)
					edata->elevel = NOTICE;
				else if (strcmp(value, "WARNING") == 0)
					edata->elevel = WARNING;
				else if (strcmp(value, "ERROR") == 0)
					edata->elevel = ERROR;
				else if (strcmp(value, "FATAL") == 0)
					edata->elevel = FATAL;
				else if (strcmp(value, "PANIC") == 0)
					edata->elevel = PANIC;
				else
					elog(ERROR, "unrecognized error severity: \"%s\"", value);
				break;
			case PG_DIAG_SQLSTATE:
				if (strlen(value) != 5)
					elog(ERROR, "invalid SQLSTATE: \"%s\"", value);
				edata->sqlerrcode = MAKE_SQLSTATE(value[0], value[1], value[2],
												  value[3], value[4]);
				break;
			case PG_DIAG_MESSAGE_PRIMARY:
				edata->message = pstrdup(value);
				break;
			case PG_DIAG_MESSAGE_DETAIL:
				edata->detail = pstrdup(value);
				break;
			case PG_DIAG_MESSAGE_HINT:
				edata->hint = pstrdup(value);
				break;
			case PG_DIAG_STATEMENT_POSITION:
				edata->cursorpos = pg_strtoint32(value);
				break;
			case PG_DIAG_INTERNAL_POSITION:
				edata->internalpos = pg_strtoint32(value);
				break;
			case PG_DIAG_INTERNAL_QUERY:
				edata->internalquery = pstrdup(value);
				break;
			case PG_DIAG_CONTEXT:
				edata->context = pstrdup(value);
				break;
			case PG_DIAG_SCHEMA_NAME:
				edata->schema_name = pstrdup(value);
				break;
			case PG_DIAG_TABLE_NAME:
				edata->table_name = pstrdup(value);
				break;
			case PG_DIAG_COLUMN_NAME:
				edata->column_name = pstrdup(value);
				break;
			case PG_DIAG_DATATYPE_NAME:
				edata->datatype_name = pstrdup(value);
				break;
			case PG_DIAG_CONSTRAINT_NAME:
				edata->constraint_name = pstrdup(value);
				break;
			case PG_DIAG_SOURCE_FILE:
				edata->filename = pstrdup(value);
				break;
			case PG_DIAG_SOURCE_LINE:
				edata->lineno = pg_strtoint32(value);
				break;
			case PG_DIAG_SOURCE_FUNCTION:
				edata->funcname = pstrdup(value);
				break;
			default:
				elog(ERROR, "unrecognized error field code: %d", (int) code);
				break;
		}
	}
}