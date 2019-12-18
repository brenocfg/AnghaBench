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
struct lookup {int l_value; } ;
typedef  int lineno_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
#define  LC_LEAP 131 
#define  LC_LINK 130 
#define  LC_RULE 129 
#define  LC_ZONE 128 
 char* _ (char*) ; 
 struct lookup* byword (char*,struct lookup const*) ; 
 int /*<<< orphan*/  close_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eat (char const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  filename ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  free (char**) ; 
 char** getfields (char*) ; 
 int /*<<< orphan*/  inleap (char**,int) ; 
 int /*<<< orphan*/  inlink (char**,int) ; 
 int /*<<< orphan*/  inrule (char**,int) ; 
 int inzcont (char**,int) ; 
 int inzone (char**,int) ; 
 struct lookup* leap_line_codes ; 
 char const* leapsec ; 
 char* progname ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 struct lookup* zi_line_codes ; 

__attribute__((used)) static void
infile(const char *name)
{
	FILE	   *fp;
	char	  **fields;
	char	   *cp;
	const struct lookup *lp;
	int			nfields;
	bool		wantcont;
	lineno_t	num;
	char		buf[BUFSIZ];

	if (strcmp(name, "-") == 0)
	{
		name = _("standard input");
		fp = stdin;
	}
	else if ((fp = fopen(name, "r")) == NULL)
	{
		const char *e = strerror(errno);

		fprintf(stderr, _("%s: Cannot open %s: %s\n"),
				progname, name, e);
		exit(EXIT_FAILURE);
	}
	wantcont = false;
	for (num = 1;; ++num)
	{
		eat(name, num);
		if (fgets(buf, sizeof buf, fp) != buf)
			break;
		cp = strchr(buf, '\n');
		if (cp == NULL)
		{
			error(_("line too long"));
			exit(EXIT_FAILURE);
		}
		*cp = '\0';
		fields = getfields(buf);
		nfields = 0;
		while (fields[nfields] != NULL)
		{
			static char nada;

			if (strcmp(fields[nfields], "-") == 0)
				fields[nfields] = &nada;
			++nfields;
		}
		if (nfields == 0)
		{
			/* nothing to do */
		}
		else if (wantcont)
		{
			wantcont = inzcont(fields, nfields);
		}
		else
		{
			struct lookup const *line_codes
			= name == leapsec ? leap_line_codes : zi_line_codes;

			lp = byword(fields[0], line_codes);
			if (lp == NULL)
				error(_("input line of unknown type"));
			else
				switch (lp->l_value)
				{
					case LC_RULE:
						inrule(fields, nfields);
						wantcont = false;
						break;
					case LC_ZONE:
						wantcont = inzone(fields, nfields);
						break;
					case LC_LINK:
						inlink(fields, nfields);
						wantcont = false;
						break;
					case LC_LEAP:
						inleap(fields, nfields);
						wantcont = false;
						break;
					default:	/* "cannot happen" */
						fprintf(stderr,
								_("%s: panic: Invalid l_value %d\n"),
								progname, lp->l_value);
						exit(EXIT_FAILURE);
				}
		}
		free(fields);
	}
	close_file(fp, NULL, filename);
	if (wantcont)
		error(_("expected continuation line not found"));
}