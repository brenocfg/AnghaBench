#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nAffixData; char** AffixData; scalar_t__ useFlagAliases; } ;
typedef  TYPE_1__ IspellDict ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  ERRCODE_CONFIG_FILE_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 char* VoidString ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ errno ; 
 int strtol (char*,char**,int) ; 

__attribute__((used)) static char *
getAffixFlagSet(IspellDict *Conf, char *s)
{
	if (Conf->useFlagAliases && *s != '\0')
	{
		int			curaffix;
		char	   *end;

		curaffix = strtol(s, &end, 10);
		if (s == end || errno == ERANGE)
			ereport(ERROR,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("invalid affix alias \"%s\"", s)));

		if (curaffix > 0 && curaffix < Conf->nAffixData)

			/*
			 * Do not subtract 1 from curaffix because empty string was added
			 * in NIImportOOAffixes
			 */
			return Conf->AffixData[curaffix];
		else if (curaffix > Conf->nAffixData)
			ereport(ERROR,
					(errcode(ERRCODE_CONFIG_FILE_ERROR),
					 errmsg("invalid affix alias \"%s\"", s)));
		return VoidString;
	}
	else
		return s;
}