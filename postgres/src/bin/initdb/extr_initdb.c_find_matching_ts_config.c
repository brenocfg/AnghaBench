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
struct TYPE_2__ {char const* tsconfname; int /*<<< orphan*/  langname; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ pg_strcasecmp (int /*<<< orphan*/ ,char*) ; 
 char* pg_strdup (char const*) ; 
 TYPE_1__* tsearch_config_languages ; 

__attribute__((used)) static const char *
find_matching_ts_config(const char *lc_type)
{
	int			i;
	char	   *langname,
			   *ptr;

	/*
	 * Convert lc_ctype to a language name by stripping everything after an
	 * underscore (usual case) or a hyphen (Windows "locale name"; see
	 * comments at IsoLocaleName()).
	 *
	 * XXX Should ' ' be a stop character?	This would select "norwegian" for
	 * the Windows locale "Norwegian (Nynorsk)_Norway.1252".  If we do so, we
	 * should also accept the "nn" and "nb" Unix locales.
	 *
	 * Just for paranoia, we also stop at '.' or '@'.
	 */
	if (lc_type == NULL)
		langname = pg_strdup("");
	else
	{
		ptr = langname = pg_strdup(lc_type);
		while (*ptr &&
			   *ptr != '_' && *ptr != '-' && *ptr != '.' && *ptr != '@')
			ptr++;
		*ptr = '\0';
	}

	for (i = 0; tsearch_config_languages[i].tsconfname; i++)
	{
		if (pg_strcasecmp(tsearch_config_languages[i].langname, langname) == 0)
		{
			free(langname);
			return tsearch_config_languages[i].tsconfname;
		}
	}

	free(langname);
	return NULL;
}