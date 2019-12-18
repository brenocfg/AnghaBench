#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  tsearch_readline_state ;
struct TYPE_5__ {scalar_t__ nsubst; } ;
typedef  TYPE_1__ DictThesaurus ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int TR_INLEX ; 
 int TR_INSUBS ; 
 int TR_WAITLEX ; 
 int TR_WAITSUBS ; 
 int /*<<< orphan*/  addWrd (TYPE_1__*,char*,char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* get_tsearch_config_filename (char const*,char*) ; 
 int /*<<< orphan*/  newLexeme (TYPE_1__*,char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_mblen (char*) ; 
 scalar_t__ t_iseq (char*,char) ; 
 scalar_t__ t_isspace (char*) ; 
 char* tsearch_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsearch_readline_begin (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tsearch_readline_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
thesaurusRead(const char *filename, DictThesaurus *d)
{
	tsearch_readline_state trst;
	uint32		idsubst = 0;
	bool		useasis = false;
	char	   *line;

	filename = get_tsearch_config_filename(filename, "ths");
	if (!tsearch_readline_begin(&trst, filename))
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not open thesaurus file \"%s\": %m",
						filename)));

	while ((line = tsearch_readline(&trst)) != NULL)
	{
		char	   *ptr;
		int			state = TR_WAITLEX;
		char	   *beginwrd = NULL;
		uint32		posinsubst = 0;
		uint32		nwrd = 0;

		ptr = line;

		/* is it a comment? */
		while (*ptr && t_isspace(ptr))
			ptr += pg_mblen(ptr);

		if (t_iseq(ptr, '#') || *ptr == '\0' ||
			t_iseq(ptr, '\n') || t_iseq(ptr, '\r'))
		{
			pfree(line);
			continue;
		}

		while (*ptr)
		{
			if (state == TR_WAITLEX)
			{
				if (t_iseq(ptr, ':'))
				{
					if (posinsubst == 0)
						ereport(ERROR,
								(errcode(ERRCODE_CONFIG_FILE_ERROR),
								 errmsg("unexpected delimiter")));
					state = TR_WAITSUBS;
				}
				else if (!t_isspace(ptr))
				{
					beginwrd = ptr;
					state = TR_INLEX;
				}
			}
			else if (state == TR_INLEX)
			{
				if (t_iseq(ptr, ':'))
				{
					newLexeme(d, beginwrd, ptr, idsubst, posinsubst++);
					state = TR_WAITSUBS;
				}
				else if (t_isspace(ptr))
				{
					newLexeme(d, beginwrd, ptr, idsubst, posinsubst++);
					state = TR_WAITLEX;
				}
			}
			else if (state == TR_WAITSUBS)
			{
				if (t_iseq(ptr, '*'))
				{
					useasis = true;
					state = TR_INSUBS;
					beginwrd = ptr + pg_mblen(ptr);
				}
				else if (t_iseq(ptr, '\\'))
				{
					useasis = false;
					state = TR_INSUBS;
					beginwrd = ptr + pg_mblen(ptr);
				}
				else if (!t_isspace(ptr))
				{
					useasis = false;
					beginwrd = ptr;
					state = TR_INSUBS;
				}
			}
			else if (state == TR_INSUBS)
			{
				if (t_isspace(ptr))
				{
					if (ptr == beginwrd)
						ereport(ERROR,
								(errcode(ERRCODE_CONFIG_FILE_ERROR),
								 errmsg("unexpected end of line or lexeme")));
					addWrd(d, beginwrd, ptr, idsubst, nwrd++, posinsubst, useasis);
					state = TR_WAITSUBS;
				}
			}
			else
				elog(ERROR, "unrecognized thesaurus state: %d", state);

			ptr += pg_mblen(ptr);
		}

		if (state == TR_INSUBS)
		{
			if (ptr == beginwrd)
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("unexpected end of line or lexeme")));
			addWrd(d, beginwrd, ptr, idsubst, nwrd++, posinsubst, useasis);
		}

		idsubst++;

		if (!(nwrd && posinsubst))
			ereport(ERROR,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("unexpected end of line")));

		/*
		 * Note: currently, tsearch_readline can't return lines exceeding 4KB,
		 * so overflow of the word counts is impossible.  But that may not
		 * always be true, so let's check.
		 */
		if (nwrd != (uint16) nwrd || posinsubst != (uint16) posinsubst)
			ereport(ERROR,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("too many lexemes in thesaurus entry")));

		pfree(line);
	}

	d->nsubst = idsubst;

	tsearch_readline_end(&trst);
}