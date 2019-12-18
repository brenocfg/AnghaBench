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
typedef  int /*<<< orphan*/  int32 ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayBuildState ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_INVALID_TEXT_REPRESENTATION ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FALSE ; 
 int MAXDIM ; 
 scalar_t__ SvRV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  accumArrayResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** av_fetch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int av_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/ * get_perl_array_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plperl_sv_to_datum (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
array_to_datum_internal(AV *av, ArrayBuildState *astate,
						int *ndims, int *dims, int cur_depth,
						Oid arraytypid, Oid elemtypid, int32 typmod,
						FmgrInfo *finfo, Oid typioparam)
{
	dTHX;
	int			i;
	int			len = av_len(av) + 1;

	for (i = 0; i < len; i++)
	{
		/* fetch the array element */
		SV		  **svp = av_fetch(av, i, FALSE);

		/* see if this element is an array, if so get that */
		SV		   *sav = svp ? get_perl_array_ref(*svp) : NULL;

		/* multi-dimensional array? */
		if (sav)
		{
			AV		   *nav = (AV *) SvRV(sav);

			/* dimensionality checks */
			if (cur_depth + 1 > MAXDIM)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("number of array dimensions (%d) exceeds the maximum allowed (%d)",
								cur_depth + 1, MAXDIM)));

			/* set size when at first element in this level, else compare */
			if (i == 0 && *ndims == cur_depth)
			{
				dims[*ndims] = av_len(nav) + 1;
				(*ndims)++;
			}
			else if (av_len(nav) + 1 != dims[cur_depth])
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("multidimensional arrays must have array expressions with matching dimensions")));

			/* recurse to fetch elements of this sub-array */
			array_to_datum_internal(nav, astate,
									ndims, dims, cur_depth + 1,
									arraytypid, elemtypid, typmod,
									finfo, typioparam);
		}
		else
		{
			Datum		dat;
			bool		isnull;

			/* scalar after some sub-arrays at same level? */
			if (*ndims != cur_depth)
				ereport(ERROR,
						(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
						 errmsg("multidimensional arrays must have array expressions with matching dimensions")));

			dat = plperl_sv_to_datum(svp ? *svp : NULL,
									 elemtypid,
									 typmod,
									 NULL,
									 finfo,
									 typioparam,
									 &isnull);

			(void) accumArrayResult(astate, dat, isnull,
									elemtypid, CurrentMemoryContext);
		}
	}
}