#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsearch_readline_state ;
struct TYPE_9__ {int usecompound; int useFlagAliases; scalar_t__ flagMode; int nCompoundAffixFlag; char** AffixData; int lenAffixData; int nAffixData; scalar_t__ CompoundAffixFlags; } ;
typedef  TYPE_1__ IspellDict ;
typedef  int /*<<< orphan*/  CompoundAffixFlag ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FF_COMPOUNDBEGIN ; 
 int /*<<< orphan*/  FF_COMPOUNDFLAG ; 
 int /*<<< orphan*/  FF_COMPOUNDFORBIDFLAG ; 
 int /*<<< orphan*/  FF_COMPOUNDLAST ; 
 int /*<<< orphan*/  FF_COMPOUNDMIDDLE ; 
 int /*<<< orphan*/  FF_COMPOUNDONLY ; 
 int /*<<< orphan*/  FF_COMPOUNDPERMITFLAG ; 
 char FF_CROSSPRODUCT ; 
 int /*<<< orphan*/  FF_PREFIX ; 
 int /*<<< orphan*/  FF_SUFFIX ; 
 scalar_t__ FM_CHAR ; 
 scalar_t__ FM_LONG ; 
 scalar_t__ FM_NUM ; 
 int /*<<< orphan*/  NIAddAffix (TYPE_1__*,char*,char,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ STRNCMP (char*,char*) ; 
 char* VoidString ; 
 int /*<<< orphan*/  addCompoundAffixFlagValue (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  cmpcmdflag ; 
 char* cpstrdup (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  getAffixFlagSet (TYPE_1__*,char*) ; 
 int getCompoundAffixFlagValue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* lowerstr_ctx (TYPE_1__*,char*) ; 
 scalar_t__ palloc0 (int) ; 
 int parse_ooaffentry (char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/  pg_mblen (char*) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ t_iseq (char*,char) ; 
 scalar_t__ t_isspace (char*) ; 
 char* tsearch_readline (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsearch_readline_begin (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tsearch_readline_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
NIImportOOAffixes(IspellDict *Conf, const char *filename)
{
	char		type[BUFSIZ],
			   *ptype = NULL;
	char		sflag[BUFSIZ];
	char		mask[BUFSIZ],
			   *pmask;
	char		find[BUFSIZ],
			   *pfind;
	char		repl[BUFSIZ],
			   *prepl;
	bool		isSuffix = false;
	int			naffix = 0,
				curaffix = 0;
	int			sflaglen = 0;
	char		flagflags = 0;
	tsearch_readline_state trst;
	char	   *recoded;

	/* read file to find any flag */
	Conf->usecompound = false;
	Conf->useFlagAliases = false;
	Conf->flagMode = FM_CHAR;

	if (!tsearch_readline_begin(&trst, filename))
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not open affix file \"%s\": %m",
						filename)));

	while ((recoded = tsearch_readline(&trst)) != NULL)
	{
		if (*recoded == '\0' || t_isspace(recoded) || t_iseq(recoded, '#'))
		{
			pfree(recoded);
			continue;
		}

		if (STRNCMP(recoded, "COMPOUNDFLAG") == 0)
			addCompoundAffixFlagValue(Conf, recoded + strlen("COMPOUNDFLAG"),
									  FF_COMPOUNDFLAG);
		else if (STRNCMP(recoded, "COMPOUNDBEGIN") == 0)
			addCompoundAffixFlagValue(Conf, recoded + strlen("COMPOUNDBEGIN"),
									  FF_COMPOUNDBEGIN);
		else if (STRNCMP(recoded, "COMPOUNDLAST") == 0)
			addCompoundAffixFlagValue(Conf, recoded + strlen("COMPOUNDLAST"),
									  FF_COMPOUNDLAST);
		/* COMPOUNDLAST and COMPOUNDEND are synonyms */
		else if (STRNCMP(recoded, "COMPOUNDEND") == 0)
			addCompoundAffixFlagValue(Conf, recoded + strlen("COMPOUNDEND"),
									  FF_COMPOUNDLAST);
		else if (STRNCMP(recoded, "COMPOUNDMIDDLE") == 0)
			addCompoundAffixFlagValue(Conf, recoded + strlen("COMPOUNDMIDDLE"),
									  FF_COMPOUNDMIDDLE);
		else if (STRNCMP(recoded, "ONLYINCOMPOUND") == 0)
			addCompoundAffixFlagValue(Conf, recoded + strlen("ONLYINCOMPOUND"),
									  FF_COMPOUNDONLY);
		else if (STRNCMP(recoded, "COMPOUNDPERMITFLAG") == 0)
			addCompoundAffixFlagValue(Conf,
									  recoded + strlen("COMPOUNDPERMITFLAG"),
									  FF_COMPOUNDPERMITFLAG);
		else if (STRNCMP(recoded, "COMPOUNDFORBIDFLAG") == 0)
			addCompoundAffixFlagValue(Conf,
									  recoded + strlen("COMPOUNDFORBIDFLAG"),
									  FF_COMPOUNDFORBIDFLAG);
		else if (STRNCMP(recoded, "FLAG") == 0)
		{
			char	   *s = recoded + strlen("FLAG");

			while (*s && t_isspace(s))
				s += pg_mblen(s);

			if (*s)
			{
				if (STRNCMP(s, "long") == 0)
					Conf->flagMode = FM_LONG;
				else if (STRNCMP(s, "num") == 0)
					Conf->flagMode = FM_NUM;
				else if (STRNCMP(s, "default") != 0)
					ereport(ERROR,
							(errcode(ERRCODE_CONFIG_FILE_ERROR),
							 errmsg("Ispell dictionary supports only "
									"\"default\", \"long\", "
									"and \"num\" flag values")));
			}
		}

		pfree(recoded);
	}
	tsearch_readline_end(&trst);

	if (Conf->nCompoundAffixFlag > 1)
		qsort((void *) Conf->CompoundAffixFlags, Conf->nCompoundAffixFlag,
			  sizeof(CompoundAffixFlag), cmpcmdflag);

	if (!tsearch_readline_begin(&trst, filename))
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("could not open affix file \"%s\": %m",
						filename)));

	while ((recoded = tsearch_readline(&trst)) != NULL)
	{
		int			fields_read;

		if (*recoded == '\0' || t_isspace(recoded) || t_iseq(recoded, '#'))
			goto nextline;

		fields_read = parse_ooaffentry(recoded, type, sflag, find, repl, mask);

		if (ptype)
			pfree(ptype);
		ptype = lowerstr_ctx(Conf, type);

		/* First try to parse AF parameter (alias compression) */
		if (STRNCMP(ptype, "af") == 0)
		{
			/* First line is the number of aliases */
			if (!Conf->useFlagAliases)
			{
				Conf->useFlagAliases = true;
				naffix = atoi(sflag);
				if (naffix <= 0)
					ereport(ERROR,
							(errcode(ERRCODE_CONFIG_FILE_ERROR),
							 errmsg("invalid number of flag vector aliases")));

				/* Also reserve place for empty flag set */
				naffix++;

				Conf->AffixData = (char **) palloc0(naffix * sizeof(char *));
				Conf->lenAffixData = Conf->nAffixData = naffix;

				/* Add empty flag set into AffixData */
				Conf->AffixData[curaffix] = VoidString;
				curaffix++;
			}
			/* Other lines are aliases */
			else
			{
				if (curaffix < naffix)
				{
					Conf->AffixData[curaffix] = cpstrdup(Conf, sflag);
					curaffix++;
				}
				else
					ereport(ERROR,
							(errcode(ERRCODE_CONFIG_FILE_ERROR),
							 errmsg("number of aliases exceeds specified number %d",
									naffix - 1)));
			}
			goto nextline;
		}
		/* Else try to parse prefixes and suffixes */
		if (fields_read < 4 ||
			(STRNCMP(ptype, "sfx") != 0 && STRNCMP(ptype, "pfx") != 0))
			goto nextline;

		sflaglen = strlen(sflag);
		if (sflaglen == 0
			|| (sflaglen > 1 && Conf->flagMode == FM_CHAR)
			|| (sflaglen > 2 && Conf->flagMode == FM_LONG))
			goto nextline;

		/*--------
		 * Affix header. For example:
		 * SFX \ N 1
		 *--------
		 */
		if (fields_read == 4)
		{
			isSuffix = (STRNCMP(ptype, "sfx") == 0);
			if (t_iseq(find, 'y') || t_iseq(find, 'Y'))
				flagflags = FF_CROSSPRODUCT;
			else
				flagflags = 0;
		}
		/*--------
		 * Affix fields. For example:
		 * SFX \   0	Y/L [^Y]
		 *--------
		 */
		else
		{
			char	   *ptr;
			int			aflg = 0;

			/* Get flags after '/' (flags are case sensitive) */
			if ((ptr = strchr(repl, '/')) != NULL)
				aflg |= getCompoundAffixFlagValue(Conf,
												  getAffixFlagSet(Conf,
																  ptr + 1));
			/* Get lowercased version of string before '/' */
			prepl = lowerstr_ctx(Conf, repl);
			if ((ptr = strchr(prepl, '/')) != NULL)
				*ptr = '\0';
			pfind = lowerstr_ctx(Conf, find);
			pmask = lowerstr_ctx(Conf, mask);
			if (t_iseq(find, '0'))
				*pfind = '\0';
			if (t_iseq(repl, '0'))
				*prepl = '\0';

			NIAddAffix(Conf, sflag, flagflags | aflg, pmask, pfind, prepl,
					   isSuffix ? FF_SUFFIX : FF_PREFIX);
			pfree(prepl);
			pfree(pfind);
			pfree(pmask);
		}

nextline:
		pfree(recoded);
	}

	tsearch_readline_end(&trst);
	if (ptype)
		pfree(ptype);
}