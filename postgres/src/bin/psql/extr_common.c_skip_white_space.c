#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  encoding; } ;

/* Variables and functions */
 int PQmblen (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (unsigned char) ; 
 TYPE_1__ pset ; 

__attribute__((used)) static const char *
skip_white_space(const char *query)
{
	int			cnestlevel = 0; /* slash-star comment nest level */

	while (*query)
	{
		int			mblen = PQmblen(query, pset.encoding);

		/*
		 * Note: we assume the encoding is a superset of ASCII, so that for
		 * example "query[0] == '/'" is meaningful.  However, we do NOT assume
		 * that the second and subsequent bytes of a multibyte character
		 * couldn't look like ASCII characters; so it is critical to advance
		 * by mblen, not 1, whenever we haven't exactly identified the
		 * character we are skipping over.
		 */
		if (isspace((unsigned char) *query))
			query += mblen;
		else if (query[0] == '/' && query[1] == '*')
		{
			cnestlevel++;
			query += 2;
		}
		else if (cnestlevel > 0 && query[0] == '*' && query[1] == '/')
		{
			cnestlevel--;
			query += 2;
		}
		else if (cnestlevel == 0 && query[0] == '-' && query[1] == '-')
		{
			query += 2;

			/*
			 * We have to skip to end of line since any slash-star inside the
			 * -- comment does NOT start a slash-star comment.
			 */
			while (*query)
			{
				if (*query == '\n')
				{
					query++;
					break;
				}
				query += PQmblen(query, pset.encoding);
			}
		}
		else if (cnestlevel > 0)
			query += mblen;
		else
			break;				/* found first token */
	}

	return query;
}