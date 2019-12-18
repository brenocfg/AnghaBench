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
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 scalar_t__ CHAREQ (char*,char*) ; 
 int /*<<< orphan*/  CopyAdvChar (char*,char*,int) ; 
 int /*<<< orphan*/  ERRCODE_INVALID_ESCAPE_SEQUENCE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NextChar (char*,int) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 char* VARDATA (int /*<<< orphan*/ *) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  VARSIZE_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (scalar_t__) ; 

__attribute__((used)) static text *
do_like_escape(text *pat, text *esc)
{
	text	   *result;
	char	   *p,
			   *e,
			   *r;
	int			plen,
				elen;
	bool		afterescape;

	p = VARDATA_ANY(pat);
	plen = VARSIZE_ANY_EXHDR(pat);
	e = VARDATA_ANY(esc);
	elen = VARSIZE_ANY_EXHDR(esc);

	/*
	 * Worst-case pattern growth is 2x --- unlikely, but it's hardly worth
	 * trying to calculate the size more accurately than that.
	 */
	result = (text *) palloc(plen * 2 + VARHDRSZ);
	r = VARDATA(result);

	if (elen == 0)
	{
		/*
		 * No escape character is wanted.  Double any backslashes in the
		 * pattern to make them act like ordinary characters.
		 */
		while (plen > 0)
		{
			if (*p == '\\')
				*r++ = '\\';
			CopyAdvChar(r, p, plen);
		}
	}
	else
	{
		/*
		 * The specified escape must be only a single character.
		 */
		NextChar(e, elen);
		if (elen != 0)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_ESCAPE_SEQUENCE),
					 errmsg("invalid escape string"),
					 errhint("Escape string must be empty or one character.")));

		e = VARDATA_ANY(esc);

		/*
		 * If specified escape is '\', just copy the pattern as-is.
		 */
		if (*e == '\\')
		{
			memcpy(result, pat, VARSIZE_ANY(pat));
			return result;
		}

		/*
		 * Otherwise, convert occurrences of the specified escape character to
		 * '\', and double occurrences of '\' --- unless they immediately
		 * follow an escape character!
		 */
		afterescape = false;
		while (plen > 0)
		{
			if (CHAREQ(p, e) && !afterescape)
			{
				*r++ = '\\';
				NextChar(p, plen);
				afterescape = true;
			}
			else if (*p == '\\')
			{
				*r++ = '\\';
				if (!afterescape)
					*r++ = '\\';
				NextChar(p, plen);
				afterescape = false;
			}
			else
			{
				CopyAdvChar(r, p, plen);
				afterescape = false;
			}
		}
	}

	SET_VARSIZE(result, r - ((char *) result));

	return result;
}