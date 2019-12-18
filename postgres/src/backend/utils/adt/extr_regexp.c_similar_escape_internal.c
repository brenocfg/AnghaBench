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
 int /*<<< orphan*/  ERRCODE_INVALID_ESCAPE_SEQUENCE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_USE_OF_ESCAPE_CHARACTER ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,int) ; 
 char* VARDATA (int /*<<< orphan*/ *) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int pg_mblen (char*) ; 
 int pg_mbstrlen_with_len (char*,int) ; 

__attribute__((used)) static text *
similar_escape_internal(text *pat_text, text *esc_text)
{
	text	   *result;
	char	   *p,
			   *e,
			   *r;
	int			plen,
				elen;
	bool		afterescape = false;
	bool		incharclass = false;
	int			nquotes = 0;

	p = VARDATA_ANY(pat_text);
	plen = VARSIZE_ANY_EXHDR(pat_text);
	if (esc_text == NULL)
	{
		/* No ESCAPE clause provided; default to backslash as escape */
		e = "\\";
		elen = 1;
	}
	else
	{
		e = VARDATA_ANY(esc_text);
		elen = VARSIZE_ANY_EXHDR(esc_text);
		if (elen == 0)
			e = NULL;			/* no escape character */
		else if (elen > 1)
		{
			int			escape_mblen = pg_mbstrlen_with_len(e, elen);

			if (escape_mblen > 1)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_ESCAPE_SEQUENCE),
						 errmsg("invalid escape string"),
						 errhint("Escape string must be empty or one character.")));
		}
	}

	/*----------
	 * We surround the transformed input string with
	 *			^(?: ... )$
	 * which requires some explanation.  We need "^" and "$" to force
	 * the pattern to match the entire input string as per the SQL spec.
	 * The "(?:" and ")" are a non-capturing set of parens; we have to have
	 * parens in case the string contains "|", else the "^" and "$" will
	 * be bound into the first and last alternatives which is not what we
	 * want, and the parens must be non capturing because we don't want them
	 * to count when selecting output for SUBSTRING.
	 *
	 * When the pattern is divided into three parts by escape-double-quotes,
	 * what we emit is
	 *			^(?:part1){1,1}?(part2){1,1}(?:part3)$
	 * which requires even more explanation.  The "{1,1}?" on part1 makes it
	 * non-greedy so that it will match the smallest possible amount of text
	 * not the largest, as required by SQL.  The plain parens around part2
	 * are capturing parens so that that part is what controls the result of
	 * SUBSTRING.  The "{1,1}" forces part2 to be greedy, so that it matches
	 * the largest possible amount of text; hence part3 must match the
	 * smallest amount of text, as required by SQL.  We don't need an explicit
	 * greediness marker on part3.  Note that this also confines the effects
	 * of any "|" characters to the respective part, which is what we want.
	 *
	 * The SQL spec says that SUBSTRING's pattern must contain exactly two
	 * escape-double-quotes, but we only complain if there's more than two.
	 * With none, we act as though part1 and part3 are empty; with one, we
	 * act as though part3 is empty.  Both behaviors fall out of omitting
	 * the relevant part separators in the above expansion.  If the result
	 * of this function is used in a plain regexp match (SIMILAR TO), the
	 * escape-double-quotes have no effect on the match behavior.
	 *----------
	 */

	/*
	 * We need room for the prefix/postfix and part separators, plus as many
	 * as 3 output bytes per input byte; since the input is at most 1GB this
	 * can't overflow size_t.
	 */
	result = (text *) palloc(VARHDRSZ + 23 + 3 * (size_t) plen);
	r = VARDATA(result);

	*r++ = '^';
	*r++ = '(';
	*r++ = '?';
	*r++ = ':';

	while (plen > 0)
	{
		char		pchar = *p;

		/*
		 * If both the escape character and the current character from the
		 * pattern are multi-byte, we need to take the slow path.
		 *
		 * But if one of them is single-byte, we can process the pattern one
		 * byte at a time, ignoring multi-byte characters.  (This works
		 * because all server-encodings have the property that a valid
		 * multi-byte character representation cannot contain the
		 * representation of a valid single-byte character.)
		 */

		if (elen > 1)
		{
			int			mblen = pg_mblen(p);

			if (mblen > 1)
			{
				/* slow, multi-byte path */
				if (afterescape)
				{
					*r++ = '\\';
					memcpy(r, p, mblen);
					r += mblen;
					afterescape = false;
				}
				else if (e && elen == mblen && memcmp(e, p, mblen) == 0)
				{
					/* SQL escape character; do not send to output */
					afterescape = true;
				}
				else
				{
					/*
					 * We know it's a multi-byte character, so we don't need
					 * to do all the comparisons to single-byte characters
					 * that we do below.
					 */
					memcpy(r, p, mblen);
					r += mblen;
				}

				p += mblen;
				plen -= mblen;

				continue;
			}
		}

		/* fast path */
		if (afterescape)
		{
			if (pchar == '"' && !incharclass)	/* escape-double-quote? */
			{
				/* emit appropriate part separator, per notes above */
				if (nquotes == 0)
				{
					*r++ = ')';
					*r++ = '{';
					*r++ = '1';
					*r++ = ',';
					*r++ = '1';
					*r++ = '}';
					*r++ = '?';
					*r++ = '(';
				}
				else if (nquotes == 1)
				{
					*r++ = ')';
					*r++ = '{';
					*r++ = '1';
					*r++ = ',';
					*r++ = '1';
					*r++ = '}';
					*r++ = '(';
					*r++ = '?';
					*r++ = ':';
				}
				else
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_USE_OF_ESCAPE_CHARACTER),
							 errmsg("SQL regular expression may not contain more than two escape-double-quote separators")));
				nquotes++;
			}
			else
			{
				/*
				 * We allow any character at all to be escaped; notably, this
				 * allows access to POSIX character-class escapes such as
				 * "\d".  The SQL spec is considerably more restrictive.
				 */
				*r++ = '\\';
				*r++ = pchar;
			}
			afterescape = false;
		}
		else if (e && pchar == *e)
		{
			/* SQL escape character; do not send to output */
			afterescape = true;
		}
		else if (incharclass)
		{
			if (pchar == '\\')
				*r++ = '\\';
			*r++ = pchar;
			if (pchar == ']')
				incharclass = false;
		}
		else if (pchar == '[')
		{
			*r++ = pchar;
			incharclass = true;
		}
		else if (pchar == '%')
		{
			*r++ = '.';
			*r++ = '*';
		}
		else if (pchar == '_')
			*r++ = '.';
		else if (pchar == '(')
		{
			/* convert to non-capturing parenthesis */
			*r++ = '(';
			*r++ = '?';
			*r++ = ':';
		}
		else if (pchar == '\\' || pchar == '.' ||
				 pchar == '^' || pchar == '$')
		{
			*r++ = '\\';
			*r++ = pchar;
		}
		else
			*r++ = pchar;
		p++, plen--;
	}

	*r++ = ')';
	*r++ = '$';

	SET_VARSIZE(result, r - ((char *) result));

	return result;
}