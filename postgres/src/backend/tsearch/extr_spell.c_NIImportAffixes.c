#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsearch_readline_state ;
struct TYPE_6__ {int usecompound; int useFlagAliases; int /*<<< orphan*/  flagMode; } ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  COPYCHAR (char*,char*) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FF_COMPOUNDFLAG ; 
 char FF_COMPOUNDONLY ; 
 char FF_CROSSPRODUCT ; 
 int /*<<< orphan*/  FF_PREFIX ; 
 int /*<<< orphan*/  FF_SUFFIX ; 
 int /*<<< orphan*/  FM_CHAR ; 
 int /*<<< orphan*/  NIAddAffix (TYPE_1__*,char*,char,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NIImportOOAffixes (TYPE_1__*,char const*) ; 
 scalar_t__ STRNCMP (char*,char*) ; 
 int /*<<< orphan*/  addCompoundAffixFlagValue (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 char* findchar2 (char*,char,char) ; 
 char* lowerstr (char*) ; 
 int /*<<< orphan*/  parse_affentry (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int pg_mblen (char*) ; 
 scalar_t__ t_isspace (char*) ; 
 char* tsearch_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsearch_readline_begin (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tsearch_readline_end (int /*<<< orphan*/ *) ; 

void
NIImportAffixes(IspellDict *Conf, const char *filename)
{
	char	   *pstr = NULL;
	char		flag[BUFSIZ];
	char		mask[BUFSIZ];
	char		find[BUFSIZ];
	char		repl[BUFSIZ];
	char	   *s;
	bool		suffixes = false;
	bool		prefixes = false;
	char		flagflags = 0;
	tsearch_readline_state trst;
	bool		oldformat = false;
	char	   *recoded = NULL;

	if (!tsearch_readline_begin(&trst, filename))
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not open affix file \"%s\": %m",
						filename)));

	Conf->usecompound = false;
	Conf->useFlagAliases = false;
	Conf->flagMode = FM_CHAR;

	while ((recoded = tsearch_readline(&trst)) != NULL)
	{
		pstr = lowerstr(recoded);

		/* Skip comments and empty lines */
		if (*pstr == '#' || *pstr == '\n')
			goto nextline;

		if (STRNCMP(pstr, "compoundwords") == 0)
		{
			/* Find case-insensitive L flag in non-lowercased string */
			s = findchar2(recoded, 'l', 'L');
			if (s)
			{
				while (*s && !t_isspace(s))
					s += pg_mblen(s);
				while (*s && t_isspace(s))
					s += pg_mblen(s);

				if (*s && pg_mblen(s) == 1)
				{
					addCompoundAffixFlagValue(Conf, s, FF_COMPOUNDFLAG);
					Conf->usecompound = true;
				}
				oldformat = true;
				goto nextline;
			}
		}
		if (STRNCMP(pstr, "suffixes") == 0)
		{
			suffixes = true;
			prefixes = false;
			oldformat = true;
			goto nextline;
		}
		if (STRNCMP(pstr, "prefixes") == 0)
		{
			suffixes = false;
			prefixes = true;
			oldformat = true;
			goto nextline;
		}
		if (STRNCMP(pstr, "flag") == 0)
		{
			s = recoded + 4;	/* we need non-lowercased string */
			flagflags = 0;

			while (*s && t_isspace(s))
				s += pg_mblen(s);

			if (*s == '*')
			{
				flagflags |= FF_CROSSPRODUCT;
				s++;
			}
			else if (*s == '~')
			{
				flagflags |= FF_COMPOUNDONLY;
				s++;
			}

			if (*s == '\\')
				s++;

			/*
			 * An old-format flag is a single ASCII character; we expect it to
			 * be followed by EOL, whitespace, or ':'.  Otherwise this is a
			 * new-format flag command.
			 */
			if (*s && pg_mblen(s) == 1)
			{
				COPYCHAR(flag, s);
				flag[1] = '\0';

				s++;
				if (*s == '\0' || *s == '#' || *s == '\n' || *s == ':' ||
					t_isspace(s))
				{
					oldformat = true;
					goto nextline;
				}
			}
			goto isnewformat;
		}
		if (STRNCMP(recoded, "COMPOUNDFLAG") == 0 ||
			STRNCMP(recoded, "COMPOUNDMIN") == 0 ||
			STRNCMP(recoded, "PFX") == 0 ||
			STRNCMP(recoded, "SFX") == 0)
			goto isnewformat;

		if ((!suffixes) && (!prefixes))
			goto nextline;

		if (!parse_affentry(pstr, mask, find, repl))
			goto nextline;

		NIAddAffix(Conf, flag, flagflags, mask, find, repl, suffixes ? FF_SUFFIX : FF_PREFIX);

nextline:
		pfree(recoded);
		pfree(pstr);
	}
	tsearch_readline_end(&trst);
	return;

isnewformat:
	if (oldformat)
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("affix file contains both old-style and new-style commands")));
	tsearch_readline_end(&trst);

	NIImportOOAffixes(Conf, filename);
}