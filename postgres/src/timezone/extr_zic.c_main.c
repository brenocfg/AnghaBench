#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ptrdiff_t ;
struct TYPE_5__ {char* l_filename; int l_linenum; char* l_from; char* l_to; } ;
struct TYPE_4__ {int /*<<< orphan*/ * z_name; } ;

/* Variables and functions */
 int EOF ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 char* PG_VERSION ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int TYPE_BIT (int /*<<< orphan*/ ) ; 
 char* TZDEFAULT ; 
 char* TZDEFRULES ; 
 char* ZIC_BLOAT_DEFAULT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  adjleap () ; 
 int /*<<< orphan*/  associate () ; 
 int bloat ; 
 int /*<<< orphan*/  change_directory (char*) ; 
 int /*<<< orphan*/  close_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* directory ; 
 int /*<<< orphan*/  dolink (char*,char*,int) ; 
 int /*<<< orphan*/  eat (char*,int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 scalar_t__ errors ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  infile (char*) ; 
 char* lcltime ; 
 char* leapsec ; 
 TYPE_3__* links ; 
 int nlinks ; 
 int noise ; 
 int nzones ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  outzone (TYPE_1__*,int) ; 
 int print_abbrevs ; 
 int /*<<< orphan*/  print_cutoff ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* progname ; 
 char* psxrules ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timerange_option (char*) ; 
 char* tzdefault ; 
 int umask (int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warning (char*) ; 
 scalar_t__ warnings ; 
 char* yitcommand ; 
 int /*<<< orphan*/  zic_t ; 
 TYPE_1__* zones ; 

int
main(int argc, char **argv)
{
	int			c,
				k;
	ptrdiff_t	i,
				j;
	bool		timerange_given = false;

#ifndef WIN32
	umask(umask(S_IWGRP | S_IWOTH) | (S_IWGRP | S_IWOTH));
#endif
	progname = argv[0];
	if (TYPE_BIT(zic_t) <64)
	{
		fprintf(stderr, "%s: %s\n", progname,
				_("wild compilation-time specification of zic_t"));
		return EXIT_FAILURE;
	}
	for (k = 1; k < argc; k++)
		if (strcmp(argv[k], "--version") == 0)
		{
			printf("zic %s\n", PG_VERSION);
			close_file(stdout, NULL, NULL);
			return EXIT_SUCCESS;
		}
		else if (strcmp(argv[k], "--help") == 0)
		{
			usage(stdout, EXIT_SUCCESS);
		}
	while ((c = getopt(argc, argv, "b:d:l:L:p:Pr:st:vy:")) != EOF && c != -1)
		switch (c)
		{
			default:
				usage(stderr, EXIT_FAILURE);
			case 'b':
				if (strcmp(optarg, "slim") == 0)
				{
					if (0 < bloat)
						error(_("incompatible -b options"));
					bloat = -1;
				}
				else if (strcmp(optarg, "fat") == 0)
				{
					if (bloat < 0)
						error(_("incompatible -b options"));
					bloat = 1;
				}
				else
					error(_("invalid option: -b '%s'"), optarg);
				break;
			case 'd':
				if (directory == NULL)
					directory = strdup(optarg);
				else
				{
					fprintf(stderr,
							_("%s: More than one -d option specified\n"),
							progname);
					return EXIT_FAILURE;
				}
				break;
			case 'l':
				if (lcltime == NULL)
					lcltime = strdup(optarg);
				else
				{
					fprintf(stderr,
							_("%s: More than one -l option specified\n"),
							progname);
					return EXIT_FAILURE;
				}
				break;
			case 'p':
				if (psxrules == NULL)
					psxrules = strdup(optarg);
				else
				{
					fprintf(stderr,
							_("%s: More than one -p option specified\n"),
							progname);
					return EXIT_FAILURE;
				}
				break;
			case 't':
				if (tzdefault != NULL)
				{
					fprintf(stderr,
							_("%s: More than one -t option"
							  " specified\n"),
							progname);
					return EXIT_FAILURE;
				}
				tzdefault = optarg;
				break;
			case 'y':
				if (yitcommand == NULL)
				{
					warning(_("-y is obsolescent"));
					yitcommand = strdup(optarg);
				}
				else
				{
					fprintf(stderr,
							_("%s: More than one -y option specified\n"),
							progname);
					return EXIT_FAILURE;
				}
				break;
			case 'L':
				if (leapsec == NULL)
					leapsec = strdup(optarg);
				else
				{
					fprintf(stderr,
							_("%s: More than one -L option specified\n"),
							progname);
					return EXIT_FAILURE;
				}
				break;
			case 'v':
				noise = true;
				break;
			case 'P':
				print_abbrevs = true;
				print_cutoff = time(NULL);
				break;
			case 'r':
				if (timerange_given)
				{
					fprintf(stderr,
							_("%s: More than one -r option specified\n"),
							progname);
					return EXIT_FAILURE;
				}
				if (!timerange_option(optarg))
				{
					fprintf(stderr,
							_("%s: invalid time range: %s\n"),
							progname, optarg);
					return EXIT_FAILURE;
				}
				timerange_given = true;
				break;
			case 's':
				warning(_("-s ignored"));
				break;
		}
	if (optind == argc - 1 && strcmp(argv[optind], "=") == 0)
		usage(stderr, EXIT_FAILURE);	/* usage message by request */
	if (bloat == 0)
		bloat = strcmp(ZIC_BLOAT_DEFAULT, "slim") == 0 ? -1 : 1;
	if (directory == NULL)
		directory = "data";
	if (tzdefault == NULL)
		tzdefault = TZDEFAULT;
	if (yitcommand == NULL)
		yitcommand = "yearistype";

	if (optind < argc && leapsec != NULL)
	{
		infile(leapsec);
		adjleap();
	}

	for (k = optind; k < argc; k++)
		infile(argv[k]);
	if (errors)
		return EXIT_FAILURE;
	associate();
	change_directory(directory);
	for (i = 0; i < nzones; i = j)
	{
		/*
		 * Find the next non-continuation zone entry.
		 */
		for (j = i + 1; j < nzones && zones[j].z_name == NULL; ++j)
			continue;
		outzone(&zones[i], j - i);
	}

	/*
	 * Make links.
	 */
	for (i = 0; i < nlinks; ++i)
	{
		eat(links[i].l_filename, links[i].l_linenum);
		dolink(links[i].l_from, links[i].l_to, false);
		if (noise)
			for (j = 0; j < nlinks; ++j)
				if (strcmp(links[i].l_to,
						   links[j].l_from) == 0)
					warning(_("link to link"));
	}
	if (lcltime != NULL)
	{
		eat(_("command line"), 1);
		dolink(lcltime, tzdefault, true);
	}
	if (psxrules != NULL)
	{
		eat(_("command line"), 1);
		dolink(psxrules, TZDEFRULES, true);
	}
	if (warnings && (ferror(stderr) || fclose(stderr) != 0))
		return EXIT_FAILURE;
	return errors ? EXIT_FAILURE : EXIT_SUCCESS;
}