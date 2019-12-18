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
typedef  int /*<<< orphan*/  trgm ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CPTRGM (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  compact_trigram (int /*<<< orphan*/ *,char*,int) ; 
 int pg_mblen (char*) ; 

__attribute__((used)) static trgm *
make_trigrams(trgm *tptr, char *str, int bytelen, int charlen)
{
	char	   *ptr = str;

	if (charlen < 3)
		return tptr;

	if (bytelen > charlen)
	{
		/* Find multibyte character boundaries and apply compact_trigram */
		int			lenfirst = pg_mblen(str),
					lenmiddle = pg_mblen(str + lenfirst),
					lenlast = pg_mblen(str + lenfirst + lenmiddle);

		while ((ptr - str) + lenfirst + lenmiddle + lenlast <= bytelen)
		{
			compact_trigram(tptr, ptr, lenfirst + lenmiddle + lenlast);

			ptr += lenfirst;
			tptr++;

			lenfirst = lenmiddle;
			lenmiddle = lenlast;
			lenlast = pg_mblen(ptr + lenfirst + lenmiddle);
		}
	}
	else
	{
		/* Fast path when there are no multibyte characters */
		Assert(bytelen == charlen);

		while (ptr - str < bytelen - 2 /* number of trigrams = strlen - 2 */ )
		{
			CPTRGM(tptr, ptr);
			ptr++;
			tptr++;
		}
	}

	return tptr;
}