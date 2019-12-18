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
 scalar_t__ match_prosrc_to_literal (char const*,char const*,int,int*) ; 
 int pg_mbstrlen_with_len (char const*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

__attribute__((used)) static int
match_prosrc_to_query(const char *prosrc, const char *queryText,
					  int cursorpos)
{
	/*
	 * Rather than fully parsing the original command, we just scan the
	 * command looking for $prosrc$ or 'prosrc'.  This could be fooled (though
	 * not in any very probable scenarios), so fail if we find more than one
	 * match.
	 */
	int			prosrclen = strlen(prosrc);
	int			querylen = strlen(queryText);
	int			matchpos = 0;
	int			curpos;
	int			newcursorpos;

	for (curpos = 0; curpos < querylen - prosrclen; curpos++)
	{
		if (queryText[curpos] == '$' &&
			strncmp(prosrc, &queryText[curpos + 1], prosrclen) == 0 &&
			queryText[curpos + 1 + prosrclen] == '$')
		{
			/*
			 * Found a $foo$ match.  Since there are no embedded quoting
			 * characters in a dollar-quoted literal, we don't have to do any
			 * fancy arithmetic; just offset by the starting position.
			 */
			if (matchpos)
				return 0;		/* multiple matches, fail */
			matchpos = pg_mbstrlen_with_len(queryText, curpos + 1)
				+ cursorpos;
		}
		else if (queryText[curpos] == '\'' &&
				 match_prosrc_to_literal(prosrc, &queryText[curpos + 1],
										 cursorpos, &newcursorpos))
		{
			/*
			 * Found a 'foo' match.  match_prosrc_to_literal() has adjusted
			 * for any quotes or backslashes embedded in the literal.
			 */
			if (matchpos)
				return 0;		/* multiple matches, fail */
			matchpos = pg_mbstrlen_with_len(queryText, curpos + 1)
				+ newcursorpos;
		}
	}

	return matchpos;
}