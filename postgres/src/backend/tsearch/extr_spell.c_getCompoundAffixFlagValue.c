#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_9__ {int value; } ;
struct TYPE_8__ {int /*<<< orphan*/  nCompoundAffixFlag; scalar_t__ CompoundAffixFlags; } ;
typedef  TYPE_1__ IspellDict ;
typedef  TYPE_2__ CompoundAffixFlag ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ bsearch (TYPE_2__*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpcmdflag ; 
 int /*<<< orphan*/  getNextFlagFromString (TYPE_1__*,char**,char*) ; 
 int /*<<< orphan*/  setCompoundAffixFlagValue (TYPE_1__*,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getCompoundAffixFlagValue(IspellDict *Conf, char *s)
{
	uint32		flag = 0;
	CompoundAffixFlag *found,
				key;
	char		sflag[BUFSIZ];
	char	   *flagcur;

	if (Conf->nCompoundAffixFlag == 0)
		return 0;

	flagcur = s;
	while (*flagcur)
	{
		getNextFlagFromString(Conf, &flagcur, sflag);
		setCompoundAffixFlagValue(Conf, &key, sflag, 0);

		found = (CompoundAffixFlag *)
			bsearch(&key, (void *) Conf->CompoundAffixFlags,
					Conf->nCompoundAffixFlag, sizeof(CompoundAffixFlag),
					cmpcmdflag);
		if (found != NULL)
			flag |= found->value;
	}

	return flag;
}