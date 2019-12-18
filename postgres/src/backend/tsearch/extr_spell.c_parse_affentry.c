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

/* Variables and functions */
 int /*<<< orphan*/  COPYCHAR (char*,char*) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int PAE_INFIND ; 
 int PAE_INMASK ; 
 int PAE_INREPL ; 
 int PAE_WAIT_FIND ; 
 int PAE_WAIT_MASK ; 
 int PAE_WAIT_REPL ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  pg_mblen (char*) ; 
 scalar_t__ t_isalpha (char*) ; 
 scalar_t__ t_iseq (char*,char) ; 
 int /*<<< orphan*/  t_isspace (char*) ; 

__attribute__((used)) static bool
parse_affentry(char *str, char *mask, char *find, char *repl)
{
	int			state = PAE_WAIT_MASK;
	char	   *pmask = mask,
			   *pfind = find,
			   *prepl = repl;

	*mask = *find = *repl = '\0';

	while (*str)
	{
		if (state == PAE_WAIT_MASK)
		{
			if (t_iseq(str, '#'))
				return false;
			else if (!t_isspace(str))
			{
				COPYCHAR(pmask, str);
				pmask += pg_mblen(str);
				state = PAE_INMASK;
			}
		}
		else if (state == PAE_INMASK)
		{
			if (t_iseq(str, '>'))
			{
				*pmask = '\0';
				state = PAE_WAIT_FIND;
			}
			else if (!t_isspace(str))
			{
				COPYCHAR(pmask, str);
				pmask += pg_mblen(str);
			}
		}
		else if (state == PAE_WAIT_FIND)
		{
			if (t_iseq(str, '-'))
			{
				state = PAE_INFIND;
			}
			else if (t_isalpha(str) || t_iseq(str, '\'') /* english 's */ )
			{
				COPYCHAR(prepl, str);
				prepl += pg_mblen(str);
				state = PAE_INREPL;
			}
			else if (!t_isspace(str))
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("syntax error")));
		}
		else if (state == PAE_INFIND)
		{
			if (t_iseq(str, ','))
			{
				*pfind = '\0';
				state = PAE_WAIT_REPL;
			}
			else if (t_isalpha(str))
			{
				COPYCHAR(pfind, str);
				pfind += pg_mblen(str);
			}
			else if (!t_isspace(str))
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("syntax error")));
		}
		else if (state == PAE_WAIT_REPL)
		{
			if (t_iseq(str, '-'))
			{
				break;			/* void repl */
			}
			else if (t_isalpha(str))
			{
				COPYCHAR(prepl, str);
				prepl += pg_mblen(str);
				state = PAE_INREPL;
			}
			else if (!t_isspace(str))
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("syntax error")));
		}
		else if (state == PAE_INREPL)
		{
			if (t_iseq(str, '#'))
			{
				*prepl = '\0';
				break;
			}
			else if (t_isalpha(str))
			{
				COPYCHAR(prepl, str);
				prepl += pg_mblen(str);
			}
			else if (!t_isspace(str))
				ereport(ERROR,
						(errcode(ERRCODE_CONFIG_FILE_ERROR),
						 errmsg("syntax error")));
		}
		else
			elog(ERROR, "unrecognized state in parse_affentry: %d", state);

		str += pg_mblen(str);
	}

	*pmask = *pfind = *prepl = '\0';

	return (*mask && (*find || *repl));
}