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
struct tztry {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ MAXPGPATH ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ TZ_STRLEN_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char** pgfnames (char*) ; 
 int /*<<< orphan*/  pgfnames_cleanup (char**) ; 
 int score_timezone (char*,struct tztry*) ; 
 int /*<<< orphan*/  snprintf (char*,scalar_t__,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,scalar_t__) ; 
 int strlen (char*) ; 
 int zone_name_pref (char*) ; 

__attribute__((used)) static void
scan_available_timezones(char *tzdir, char *tzdirsub, struct tztry *tt,
						 int *bestscore, char *bestzonename)
{
	int			tzdir_orig_len = strlen(tzdir);
	char	  **names;
	char	  **namep;

	names = pgfnames(tzdir);
	if (!names)
		return;

	for (namep = names; *namep; namep++)
	{
		char	   *name = *namep;
		struct stat statbuf;

		/* Ignore . and .., plus any other "hidden" files */
		if (name[0] == '.')
			continue;

		snprintf(tzdir + tzdir_orig_len, MAXPGPATH - tzdir_orig_len,
				 "/%s", name);

		if (stat(tzdir, &statbuf) != 0)
		{
#ifdef DEBUG_IDENTIFY_TIMEZONE
			fprintf(stderr, "could not stat \"%s\": %s\n",
					tzdir, strerror(errno));
#endif
			tzdir[tzdir_orig_len] = '\0';
			continue;
		}

		if (S_ISDIR(statbuf.st_mode))
		{
			/* Recurse into subdirectory */
			scan_available_timezones(tzdir, tzdirsub, tt,
									 bestscore, bestzonename);
		}
		else
		{
			/* Load and test this file */
			int			score = score_timezone(tzdirsub, tt);

			if (score > *bestscore)
			{
				*bestscore = score;
				strlcpy(bestzonename, tzdirsub, TZ_STRLEN_MAX + 1);
			}
			else if (score == *bestscore)
			{
				/* Consider how to break a tie */
				int			namepref = (zone_name_pref(tzdirsub) -
										zone_name_pref(bestzonename));

				if (namepref > 0 ||
					(namepref == 0 &&
					 (strlen(tzdirsub) < strlen(bestzonename) ||
					  (strlen(tzdirsub) == strlen(bestzonename) &&
					   strcmp(tzdirsub, bestzonename) < 0))))
					strlcpy(bestzonename, tzdirsub, TZ_STRLEN_MAX + 1);
			}
		}

		/* Restore tzdir */
		tzdir[tzdir_orig_len] = '\0';
	}

	pgfnames_cleanup(names);
}