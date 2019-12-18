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
struct TYPE_12__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int state; int backSlash; TYPE_4__* curCmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  std_strings; } ;
struct TYPE_11__ {TYPE_2__ sqlparse; TYPE_1__ public; } ;
typedef  TYPE_3__ ArchiveHandle ;

/* Variables and functions */
 int /*<<< orphan*/  ExecuteSqlCommand (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
#define  SQL_IN_DOUBLE_QUOTE 130 
#define  SQL_IN_SINGLE_QUOTE 129 
#define  SQL_SCAN 128 
 int /*<<< orphan*/  appendPQExpBufferChar (TYPE_4__*,char) ; 
 TYPE_4__* createPQExpBuffer () ; 
 int /*<<< orphan*/  resetPQExpBuffer (TYPE_4__*) ; 

__attribute__((used)) static void
ExecuteSimpleCommands(ArchiveHandle *AH, const char *buf, size_t bufLen)
{
	const char *qry = buf;
	const char *eos = buf + bufLen;

	/* initialize command buffer if first time through */
	if (AH->sqlparse.curCmd == NULL)
		AH->sqlparse.curCmd = createPQExpBuffer();

	for (; qry < eos; qry++)
	{
		char		ch = *qry;

		/* For neatness, we skip any newlines between commands */
		if (!(ch == '\n' && AH->sqlparse.curCmd->len == 0))
			appendPQExpBufferChar(AH->sqlparse.curCmd, ch);

		switch (AH->sqlparse.state)
		{
			case SQL_SCAN:		/* Default state == 0, set in _allocAH */
				if (ch == ';')
				{
					/*
					 * We've found the end of a statement. Send it and reset
					 * the buffer.
					 */
					ExecuteSqlCommand(AH, AH->sqlparse.curCmd->data,
									  "could not execute query");
					resetPQExpBuffer(AH->sqlparse.curCmd);
				}
				else if (ch == '\'')
				{
					AH->sqlparse.state = SQL_IN_SINGLE_QUOTE;
					AH->sqlparse.backSlash = false;
				}
				else if (ch == '"')
				{
					AH->sqlparse.state = SQL_IN_DOUBLE_QUOTE;
				}
				break;

			case SQL_IN_SINGLE_QUOTE:
				/* We needn't handle '' specially */
				if (ch == '\'' && !AH->sqlparse.backSlash)
					AH->sqlparse.state = SQL_SCAN;
				else if (ch == '\\' && !AH->public.std_strings)
					AH->sqlparse.backSlash = !AH->sqlparse.backSlash;
				else
					AH->sqlparse.backSlash = false;
				break;

			case SQL_IN_DOUBLE_QUOTE:
				/* We needn't handle "" specially */
				if (ch == '"')
					AH->sqlparse.state = SQL_SCAN;
				break;
		}
	}
}