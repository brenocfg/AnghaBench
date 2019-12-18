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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  GRANDPARENTED ; 
 int TZ_MAX_CHARS ; 
 int ZIC_MAX_ABBR_LEN_WO_WARN ; 
 char* _ (char*) ; 
 int charcnt ; 
 int /*<<< orphan*/ * chars ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ is_alpha (char const) ; 
 scalar_t__ noise ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  warning (char*,char const*,char const*) ; 

__attribute__((used)) static void
newabbr(const char *string)
{
	int			i;

	if (strcmp(string, GRANDPARENTED) != 0)
	{
		const char *cp;
		const char *mp;

		cp = string;
		mp = NULL;
		while (is_alpha(*cp) || ('0' <= *cp && *cp <= '9')
			   || *cp == '-' || *cp == '+')
			++cp;
		if (noise && cp - string < 3)
			mp = _("time zone abbreviation has fewer than 3 characters");
		if (cp - string > ZIC_MAX_ABBR_LEN_WO_WARN)
			mp = _("time zone abbreviation has too many characters");
		if (*cp != '\0')
			mp = _("time zone abbreviation differs from POSIX standard");
		if (mp != NULL)
			warning("%s (%s)", mp, string);
	}
	i = strlen(string) + 1;
	if (charcnt + i > TZ_MAX_CHARS)
	{
		error(_("too many, or too long, time zone abbreviations"));
		exit(EXIT_FAILURE);
	}
	strcpy(&chars[charcnt], string);
	charcnt += i;
}