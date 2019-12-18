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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* DLSUFFIX ; 
 int MAXPGPATH ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 char* _ (char*) ; 
 scalar_t__ directory_exists (char*) ; 
 char* dlpath ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 char* inputdir ; 
 int /*<<< orphan*/  make_directory (char*) ; 
 char* outputdir ; 
 char** pgfnames (char*) ; 
 int /*<<< orphan*/  pgfnames_cleanup (char**) ; 
 char* progname ; 
 int /*<<< orphan*/  replace_string (char*,char*,char*) ; 
 int /*<<< orphan*/  rmtree (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
convert_sourcefiles_in(const char *source_subdir, const char *dest_dir, const char *dest_subdir, const char *suffix)
{
	char		testtablespace[MAXPGPATH];
	char		indir[MAXPGPATH];
	struct stat st;
	int			ret;
	char	  **name;
	char	  **names;
	int			count = 0;

	snprintf(indir, MAXPGPATH, "%s/%s", inputdir, source_subdir);

	/* Check that indir actually exists and is a directory */
	ret = stat(indir, &st);
	if (ret != 0 || !S_ISDIR(st.st_mode))
	{
		/*
		 * No warning, to avoid noise in tests that do not have these
		 * directories; for example, ecpg, contrib and src/pl.
		 */
		return;
	}

	names = pgfnames(indir);
	if (!names)
		/* Error logged in pgfnames */
		exit(2);

	snprintf(testtablespace, MAXPGPATH, "%s/testtablespace", outputdir);

#ifdef WIN32

	/*
	 * On Windows only, clean out the test tablespace dir, or create it if it
	 * doesn't exist.  On other platforms we expect the Makefile to take care
	 * of that.  (We don't migrate that functionality in here because it'd be
	 * harder to cope with platform-specific issues such as SELinux.)
	 *
	 * XXX it would be better if pg_regress.c had nothing at all to do with
	 * testtablespace, and this were handled by a .BAT file or similar on
	 * Windows.  See pgsql-hackers discussion of 2008-01-18.
	 */
	if (directory_exists(testtablespace))
		if (!rmtree(testtablespace, true))
		{
			fprintf(stderr, _("\n%s: could not remove test tablespace \"%s\"\n"),
					progname, testtablespace);
			exit(2);
		}
	make_directory(testtablespace);
#endif

	/* finally loop on each file and do the replacement */
	for (name = names; *name; name++)
	{
		char		srcfile[MAXPGPATH];
		char		destfile[MAXPGPATH];
		char		prefix[MAXPGPATH];
		FILE	   *infile,
				   *outfile;
		char		line[1024];

		/* reject filenames not finishing in ".source" */
		if (strlen(*name) < 8)
			continue;
		if (strcmp(*name + strlen(*name) - 7, ".source") != 0)
			continue;

		count++;

		/* build the full actual paths to open */
		snprintf(prefix, strlen(*name) - 6, "%s", *name);
		snprintf(srcfile, MAXPGPATH, "%s/%s", indir, *name);
		snprintf(destfile, MAXPGPATH, "%s/%s/%s.%s", dest_dir, dest_subdir,
				 prefix, suffix);

		infile = fopen(srcfile, "r");
		if (!infile)
		{
			fprintf(stderr, _("%s: could not open file \"%s\" for reading: %s\n"),
					progname, srcfile, strerror(errno));
			exit(2);
		}
		outfile = fopen(destfile, "w");
		if (!outfile)
		{
			fprintf(stderr, _("%s: could not open file \"%s\" for writing: %s\n"),
					progname, destfile, strerror(errno));
			exit(2);
		}
		while (fgets(line, sizeof(line), infile))
		{
			replace_string(line, "@abs_srcdir@", inputdir);
			replace_string(line, "@abs_builddir@", outputdir);
			replace_string(line, "@testtablespace@", testtablespace);
			replace_string(line, "@libdir@", dlpath);
			replace_string(line, "@DLSUFFIX@", DLSUFFIX);
			fputs(line, outfile);
		}
		fclose(infile);
		fclose(outfile);
	}

	/*
	 * If we didn't process any files, complain because it probably means
	 * somebody neglected to pass the needed --inputdir argument.
	 */
	if (count <= 0)
	{
		fprintf(stderr, _("%s: no *.source files found in \"%s\"\n"),
				progname, indir);
		exit(2);
	}

	pgfnames_cleanup(names);
}