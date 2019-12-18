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
typedef  int /*<<< orphan*/  VarString ;
typedef  int /*<<< orphan*/  SortSupport ;
typedef  scalar_t__ Datum ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetVarStringPP (scalar_t__) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 
 int varstrfastcmp_locale (char*,int,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
varlenafastcmp_locale(Datum x, Datum y, SortSupport ssup)
{
	VarString  *arg1 = DatumGetVarStringPP(x);
	VarString  *arg2 = DatumGetVarStringPP(y);
	char	   *a1p,
			   *a2p;
	int			len1,
				len2,
				result;

	a1p = VARDATA_ANY(arg1);
	a2p = VARDATA_ANY(arg2);

	len1 = VARSIZE_ANY_EXHDR(arg1);
	len2 = VARSIZE_ANY_EXHDR(arg2);

	result = varstrfastcmp_locale(a1p, len1, a2p, len2, ssup);

	/* We can't afford to leak memory here. */
	if (PointerGetDatum(arg1) != x)
		pfree(arg1);
	if (PointerGetDatum(arg2) != y)
		pfree(arg2);

	return result;
}