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
typedef  int /*<<< orphan*/  SortSupport ;
typedef  scalar_t__ Datum ;
typedef  int /*<<< orphan*/  BpChar ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetBpCharPP (scalar_t__) ; 
 int /*<<< orphan*/  Min (int,int) ; 
 scalar_t__ PointerGetDatum (int /*<<< orphan*/ *) ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int bpchartruelen (char*,int /*<<< orphan*/ ) ; 
 int memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bpcharfastcmp_c(Datum x, Datum y, SortSupport ssup)
{
	BpChar	   *arg1 = DatumGetBpCharPP(x);
	BpChar	   *arg2 = DatumGetBpCharPP(y);
	char	   *a1p,
			   *a2p;
	int			len1,
				len2,
				result;

	a1p = VARDATA_ANY(arg1);
	a2p = VARDATA_ANY(arg2);

	len1 = bpchartruelen(a1p, VARSIZE_ANY_EXHDR(arg1));
	len2 = bpchartruelen(a2p, VARSIZE_ANY_EXHDR(arg2));

	result = memcmp(a1p, a2p, Min(len1, len2));
	if ((result == 0) && (len1 != len2))
		result = (len1 < len2) ? -1 : 1;

	/* We can't afford to leak memory here. */
	if (PointerGetDatum(arg1) != x)
		pfree(arg1);
	if (PointerGetDatum(arg2) != y)
		pfree(arg2);

	return result;
}