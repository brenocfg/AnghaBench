#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WordEntryPos ;
struct TYPE_3__ {char* word; char* prsbuf; int /*<<< orphan*/  bufstart; scalar_t__ oprisdelim; scalar_t__ is_web; } ;
typedef  TYPE_1__* TSVectorParseState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  COPYCHAR (char*,char*) ; 
 int /*<<< orphan*/  ERRCODE_SYNTAX_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int INPOSINFO ; 
 scalar_t__ ISOPERATOR (char*) ; 
 int /*<<< orphan*/  LIMITPOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRSSYNTAXERROR ; 
 int /*<<< orphan*/  RESIZEPRSBUF ; 
 int /*<<< orphan*/  RETURN_TOKEN ; 
 int WAITCHARCMPLX ; 
 int WAITENDCMPLX ; 
 int WAITENDWORD ; 
 int WAITNEXTCHAR ; 
 int WAITPOSDELIM ; 
 int WAITPOSINFO ; 
 int WAITWORD ; 
 scalar_t__ WEP_GETPOS (int /*<<< orphan*/ ) ; 
 scalar_t__ WEP_GETWEIGHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEP_SETPOS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEP_SETWEIGHT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ pg_mblen (char*) ; 
 scalar_t__ repalloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ t_isdigit (char*) ; 
 scalar_t__ t_iseq (char*,char) ; 
 scalar_t__ t_isspace (char*) ; 

bool
gettoken_tsvector(TSVectorParseState state,
				  char **strval, int *lenval,
				  WordEntryPos **pos_ptr, int *poslen,
				  char **endptr)
{
	int			oldstate = 0;
	char	   *curpos = state->word;
	int			statecode = WAITWORD;

	/*
	 * pos is for collecting the comma delimited list of positions followed by
	 * the actual token.
	 */
	WordEntryPos *pos = NULL;
	int			npos = 0;		/* elements of pos used */
	int			posalen = 0;	/* allocated size of pos */

	while (1)
	{
		if (statecode == WAITWORD)
		{
			if (*(state->prsbuf) == '\0')
				return false;
			else if (!state->is_web && t_iseq(state->prsbuf, '\''))
				statecode = WAITENDCMPLX;
			else if (!state->is_web && t_iseq(state->prsbuf, '\\'))
			{
				statecode = WAITNEXTCHAR;
				oldstate = WAITENDWORD;
			}
			else if ((state->oprisdelim && ISOPERATOR(state->prsbuf)) ||
					 (state->is_web && t_iseq(state->prsbuf, '"')))
				PRSSYNTAXERROR;
			else if (!t_isspace(state->prsbuf))
			{
				COPYCHAR(curpos, state->prsbuf);
				curpos += pg_mblen(state->prsbuf);
				statecode = WAITENDWORD;
			}
		}
		else if (statecode == WAITNEXTCHAR)
		{
			if (*(state->prsbuf) == '\0')
				ereport(ERROR,
						(errcode(ERRCODE_SYNTAX_ERROR),
						 errmsg("there is no escaped character: \"%s\"",
								state->bufstart)));
			else
			{
				RESIZEPRSBUF;
				COPYCHAR(curpos, state->prsbuf);
				curpos += pg_mblen(state->prsbuf);
				Assert(oldstate != 0);
				statecode = oldstate;
			}
		}
		else if (statecode == WAITENDWORD)
		{
			if (!state->is_web && t_iseq(state->prsbuf, '\\'))
			{
				statecode = WAITNEXTCHAR;
				oldstate = WAITENDWORD;
			}
			else if (t_isspace(state->prsbuf) || *(state->prsbuf) == '\0' ||
					 (state->oprisdelim && ISOPERATOR(state->prsbuf)) ||
					 (state->is_web && t_iseq(state->prsbuf, '"')))
			{
				RESIZEPRSBUF;
				if (curpos == state->word)
					PRSSYNTAXERROR;
				*(curpos) = '\0';
				RETURN_TOKEN;
			}
			else if (t_iseq(state->prsbuf, ':'))
			{
				if (curpos == state->word)
					PRSSYNTAXERROR;
				*(curpos) = '\0';
				if (state->oprisdelim)
					RETURN_TOKEN;
				else
					statecode = INPOSINFO;
			}
			else
			{
				RESIZEPRSBUF;
				COPYCHAR(curpos, state->prsbuf);
				curpos += pg_mblen(state->prsbuf);
			}
		}
		else if (statecode == WAITENDCMPLX)
		{
			if (!state->is_web && t_iseq(state->prsbuf, '\''))
			{
				statecode = WAITCHARCMPLX;
			}
			else if (!state->is_web && t_iseq(state->prsbuf, '\\'))
			{
				statecode = WAITNEXTCHAR;
				oldstate = WAITENDCMPLX;
			}
			else if (*(state->prsbuf) == '\0')
				PRSSYNTAXERROR;
			else
			{
				RESIZEPRSBUF;
				COPYCHAR(curpos, state->prsbuf);
				curpos += pg_mblen(state->prsbuf);
			}
		}
		else if (statecode == WAITCHARCMPLX)
		{
			if (!state->is_web && t_iseq(state->prsbuf, '\''))
			{
				RESIZEPRSBUF;
				COPYCHAR(curpos, state->prsbuf);
				curpos += pg_mblen(state->prsbuf);
				statecode = WAITENDCMPLX;
			}
			else
			{
				RESIZEPRSBUF;
				*(curpos) = '\0';
				if (curpos == state->word)
					PRSSYNTAXERROR;
				if (state->oprisdelim)
				{
					/* state->prsbuf+=pg_mblen(state->prsbuf); */
					RETURN_TOKEN;
				}
				else
					statecode = WAITPOSINFO;
				continue;		/* recheck current character */
			}
		}
		else if (statecode == WAITPOSINFO)
		{
			if (t_iseq(state->prsbuf, ':'))
				statecode = INPOSINFO;
			else
				RETURN_TOKEN;
		}
		else if (statecode == INPOSINFO)
		{
			if (t_isdigit(state->prsbuf))
			{
				if (posalen == 0)
				{
					posalen = 4;
					pos = (WordEntryPos *) palloc(sizeof(WordEntryPos) * posalen);
					npos = 0;
				}
				else if (npos + 1 >= posalen)
				{
					posalen *= 2;
					pos = (WordEntryPos *) repalloc(pos, sizeof(WordEntryPos) * posalen);
				}
				npos++;
				WEP_SETPOS(pos[npos - 1], LIMITPOS(atoi(state->prsbuf)));
				/* we cannot get here in tsquery, so no need for 2 errmsgs */
				if (WEP_GETPOS(pos[npos - 1]) == 0)
					ereport(ERROR,
							(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("wrong position info in tsvector: \"%s\"",
									state->bufstart)));
				WEP_SETWEIGHT(pos[npos - 1], 0);
				statecode = WAITPOSDELIM;
			}
			else
				PRSSYNTAXERROR;
		}
		else if (statecode == WAITPOSDELIM)
		{
			if (t_iseq(state->prsbuf, ','))
				statecode = INPOSINFO;
			else if (t_iseq(state->prsbuf, 'a') || t_iseq(state->prsbuf, 'A') || t_iseq(state->prsbuf, '*'))
			{
				if (WEP_GETWEIGHT(pos[npos - 1]))
					PRSSYNTAXERROR;
				WEP_SETWEIGHT(pos[npos - 1], 3);
			}
			else if (t_iseq(state->prsbuf, 'b') || t_iseq(state->prsbuf, 'B'))
			{
				if (WEP_GETWEIGHT(pos[npos - 1]))
					PRSSYNTAXERROR;
				WEP_SETWEIGHT(pos[npos - 1], 2);
			}
			else if (t_iseq(state->prsbuf, 'c') || t_iseq(state->prsbuf, 'C'))
			{
				if (WEP_GETWEIGHT(pos[npos - 1]))
					PRSSYNTAXERROR;
				WEP_SETWEIGHT(pos[npos - 1], 1);
			}
			else if (t_iseq(state->prsbuf, 'd') || t_iseq(state->prsbuf, 'D'))
			{
				if (WEP_GETWEIGHT(pos[npos - 1]))
					PRSSYNTAXERROR;
				WEP_SETWEIGHT(pos[npos - 1], 0);
			}
			else if (t_isspace(state->prsbuf) ||
					 *(state->prsbuf) == '\0')
				RETURN_TOKEN;
			else if (!t_isdigit(state->prsbuf))
				PRSSYNTAXERROR;
		}
		else					/* internal error */
			elog(ERROR, "unrecognized state in gettoken_tsvector: %d",
				 statecode);

		/* get next char */
		state->prsbuf += pg_mblen(state->prsbuf);
	}
}