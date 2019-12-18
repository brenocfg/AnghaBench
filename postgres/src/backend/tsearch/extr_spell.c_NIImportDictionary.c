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
typedef  int /*<<< orphan*/  tsearch_readline_state ;
typedef  int /*<<< orphan*/  IspellDict ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NIAddSpell (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 char* findchar (char*,char) ; 
 char* lowerstr_ctx (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_mblen (char*) ; 
 scalar_t__ t_isprint (char*) ; 
 scalar_t__ t_isspace (char*) ; 
 char* tsearch_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsearch_readline_begin (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tsearch_readline_end (int /*<<< orphan*/ *) ; 

void
NIImportDictionary(IspellDict *Conf, const char *filename)
{
	tsearch_readline_state trst;
	char	   *line;

	if (!tsearch_readline_begin(&trst, filename))
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not open dictionary file \"%s\": %m",
						filename)));

	while ((line = tsearch_readline(&trst)) != NULL)
	{
		char	   *s,
				   *pstr;

		/* Set of affix flags */
		const char *flag;

		/* Extract flag from the line */
		flag = NULL;
		if ((s = findchar(line, '/')))
		{
			*s++ = '\0';
			flag = s;
			while (*s)
			{
				/* we allow only single encoded flags for faster works */
				if (pg_mblen(s) == 1 && t_isprint(s) && !t_isspace(s))
					s++;
				else
				{
					*s = '\0';
					break;
				}
			}
		}
		else
			flag = "";

		/* Remove trailing spaces */
		s = line;
		while (*s)
		{
			if (t_isspace(s))
			{
				*s = '\0';
				break;
			}
			s += pg_mblen(s);
		}
		pstr = lowerstr_ctx(Conf, line);

		NIAddSpell(Conf, pstr, flag);
		pfree(pstr);

		pfree(line);
	}
	tsearch_readline_end(&trst);
}