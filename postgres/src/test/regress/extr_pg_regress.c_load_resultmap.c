#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {struct TYPE_4__* next; void* resultfile; void* type; void* test; } ;
typedef  TYPE_1__ _resultmap ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int MAXPGPATH ; 
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  host_platform ; 
 char* inputdir ; 
 scalar_t__ isspace (unsigned char) ; 
 TYPE_1__* pg_malloc (int) ; 
 void* pg_strdup (char*) ; 
 char* progname ; 
 TYPE_1__* resultmap ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strerror (scalar_t__) ; 
 scalar_t__ string_matches_pattern (int /*<<< orphan*/ ,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
load_resultmap(void)
{
	char		buf[MAXPGPATH];
	FILE	   *f;

	/* scan the file ... */
	snprintf(buf, sizeof(buf), "%s/resultmap", inputdir);
	f = fopen(buf, "r");
	if (!f)
	{
		/* OK if it doesn't exist, else complain */
		if (errno == ENOENT)
			return;
		fprintf(stderr, _("%s: could not open file \"%s\" for reading: %s\n"),
				progname, buf, strerror(errno));
		exit(2);
	}

	while (fgets(buf, sizeof(buf), f))
	{
		char	   *platform;
		char	   *file_type;
		char	   *expected;
		int			i;

		/* strip trailing whitespace, especially the newline */
		i = strlen(buf);
		while (i > 0 && isspace((unsigned char) buf[i - 1]))
			buf[--i] = '\0';

		/* parse out the line fields */
		file_type = strchr(buf, ':');
		if (!file_type)
		{
			fprintf(stderr, _("incorrectly formatted resultmap entry: %s\n"),
					buf);
			exit(2);
		}
		*file_type++ = '\0';

		platform = strchr(file_type, ':');
		if (!platform)
		{
			fprintf(stderr, _("incorrectly formatted resultmap entry: %s\n"),
					buf);
			exit(2);
		}
		*platform++ = '\0';
		expected = strchr(platform, '=');
		if (!expected)
		{
			fprintf(stderr, _("incorrectly formatted resultmap entry: %s\n"),
					buf);
			exit(2);
		}
		*expected++ = '\0';

		/*
		 * if it's for current platform, save it in resultmap list. Note: by
		 * adding at the front of the list, we ensure that in ambiguous cases,
		 * the last match in the resultmap file is used. This mimics the
		 * behavior of the old shell script.
		 */
		if (string_matches_pattern(host_platform, platform))
		{
			_resultmap *entry = pg_malloc(sizeof(_resultmap));

			entry->test = pg_strdup(buf);
			entry->type = pg_strdup(file_type);
			entry->resultfile = pg_strdup(expected);
			entry->next = resultmap;
			resultmap = entry;
		}
	}
	fclose(f);
}