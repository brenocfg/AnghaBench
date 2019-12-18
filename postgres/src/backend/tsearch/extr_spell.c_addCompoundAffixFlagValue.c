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
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_4__ {int nCompoundAffixFlag; int mCompoundAffixFlag; int usecompound; int /*<<< orphan*/ * CompoundAffixFlags; } ;
typedef  TYPE_1__ IspellDict ;
typedef  int /*<<< orphan*/  CompoundAffixFlag ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  COPYCHAR (char*,char*) ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int pg_mblen (char*) ; 
 scalar_t__ repalloc (void*,int) ; 
 int /*<<< orphan*/  setCompoundAffixFlagValue (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ t_isspace (char*) ; 
 scalar_t__ tmpalloc (int) ; 

__attribute__((used)) static void
addCompoundAffixFlagValue(IspellDict *Conf, char *s, uint32 val)
{
	CompoundAffixFlag *newValue;
	char		sbuf[BUFSIZ];
	char	   *sflag;
	int			clen;

	while (*s && t_isspace(s))
		s += pg_mblen(s);

	if (!*s)
		ereport(ERROR,
				(errcode(ERRCODE_CONFIG_FILE_ERROR),
				 errmsg("syntax error")));

	/* Get flag without \n */
	sflag = sbuf;
	while (*s && !t_isspace(s) && *s != '\n')
	{
		clen = pg_mblen(s);
		COPYCHAR(sflag, s);
		sflag += clen;
		s += clen;
	}
	*sflag = '\0';

	/* Resize array or allocate memory for array CompoundAffixFlag */
	if (Conf->nCompoundAffixFlag >= Conf->mCompoundAffixFlag)
	{
		if (Conf->mCompoundAffixFlag)
		{
			Conf->mCompoundAffixFlag *= 2;
			Conf->CompoundAffixFlags = (CompoundAffixFlag *)
				repalloc((void *) Conf->CompoundAffixFlags,
						 Conf->mCompoundAffixFlag * sizeof(CompoundAffixFlag));
		}
		else
		{
			Conf->mCompoundAffixFlag = 10;
			Conf->CompoundAffixFlags = (CompoundAffixFlag *)
				tmpalloc(Conf->mCompoundAffixFlag * sizeof(CompoundAffixFlag));
		}
	}

	newValue = Conf->CompoundAffixFlags + Conf->nCompoundAffixFlag;

	setCompoundAffixFlagValue(Conf, newValue, sbuf, val);

	Conf->usecompound = true;
	Conf->nCompoundAffixFlag++;
}