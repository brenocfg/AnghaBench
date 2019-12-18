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
struct TYPE_3__ {int /*<<< orphan*/  bytes; } ;
typedef  TYPE_1__ trgm_mb_char ;
typedef  int /*<<< orphan*/  s ;
typedef  scalar_t__ pg_wchar ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_MULTIBYTE_CHAR_LEN ; 
 char* lowerstr (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_wchar2mb_with_len (scalar_t__*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static bool
convertPgWchar(pg_wchar c, trgm_mb_char *result)
{
	/* "s" has enough space for a multibyte character and a trailing NUL */
	char		s[MAX_MULTIBYTE_CHAR_LEN + 1];

	/*
	 * We can ignore the NUL character, since it can never appear in a PG text
	 * string.  This avoids the need for various special cases when
	 * reconstructing trigrams.
	 */
	if (c == 0)
		return false;

	/* Do the conversion, making sure the result is NUL-terminated */
	memset(s, 0, sizeof(s));
	pg_wchar2mb_with_len(&c, s, 1);

	/*
	 * In IGNORECASE mode, we can ignore uppercase characters.  We assume that
	 * the regex engine generated both uppercase and lowercase equivalents
	 * within each color, since we used the REG_ICASE option; so there's no
	 * need to process the uppercase version.
	 *
	 * XXX this code is dependent on the assumption that lowerstr() works the
	 * same as the regex engine's internal case folding machinery.  Might be
	 * wiser to expose pg_wc_tolower and test whether c == pg_wc_tolower(c).
	 * On the other hand, the trigrams in the index were created using
	 * lowerstr(), so we're probably screwed if there's any incompatibility
	 * anyway.
	 */
#ifdef IGNORECASE
	{
		char	   *lowerCased = lowerstr(s);

		if (strcmp(lowerCased, s) != 0)
		{
			pfree(lowerCased);
			return false;
		}
		pfree(lowerCased);
	}
#endif

	/* Fill result with exactly MAX_MULTIBYTE_CHAR_LEN bytes */
	memcpy(result->bytes, s, MAX_MULTIBYTE_CHAR_LEN);
	return true;
}