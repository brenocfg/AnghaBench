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
struct TYPE_6__ {int dscale; } ;
typedef  TYPE_1__ numeric ;
typedef  int /*<<< orphan*/  decimal ;

/* Variables and functions */
 int /*<<< orphan*/  CDECIMALTYPE ; 
 int /*<<< orphan*/  CSTRINGTYPE ; 
 int ECPG_INFORMIX_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  PGTYPESnumeric_free (TYPE_1__*) ; 
 scalar_t__ PGTYPESnumeric_from_decimal (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* PGTYPESnumeric_new () ; 
 char* PGTYPESnumeric_to_asc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ risnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rsetnull (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int
dectoasc(decimal *np, char *cp, int len, int right)
{
	char	   *str;
	numeric    *nres;

	rsetnull(CSTRINGTYPE, (char *) cp);
	if (risnull(CDECIMALTYPE, (char *) np))
		return 0;

	nres = PGTYPESnumeric_new();
	if (nres == NULL)
		return ECPG_INFORMIX_OUT_OF_MEMORY;

	if (PGTYPESnumeric_from_decimal(np, nres) != 0)
	{
		PGTYPESnumeric_free(nres);
		return ECPG_INFORMIX_OUT_OF_MEMORY;
	}

	if (right >= 0)
		str = PGTYPESnumeric_to_asc(nres, right);
	else
		str = PGTYPESnumeric_to_asc(nres, nres->dscale);

	PGTYPESnumeric_free(nres);
	if (!str)
		return -1;

	/*
	 * TODO: have to take care of len here and create exponential notation if
	 * necessary
	 */
	if ((int) (strlen(str) + 1) > len)
	{
		if (len > 1)
		{
			cp[0] = '*';
			cp[1] = '\0';
		}
		free(str);
		return -1;
	}
	else
	{
		strcpy(cp, str);
		free(str);
		return 0;
	}
}