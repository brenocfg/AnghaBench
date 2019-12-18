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
typedef  int /*<<< orphan*/  dims ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayBuildState ;
typedef  int /*<<< orphan*/  AV ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentMemoryContext ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int MAXDIM ; 
 scalar_t__ SvRV (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _sv_to_datum_finfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_to_datum_internal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int av_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_element_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * initArrayResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  makeMdArrayResult (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Datum
plperl_array_to_datum(SV *src, Oid typid, int32 typmod)
{
	dTHX;
	ArrayBuildState *astate;
	Oid			elemtypid;
	FmgrInfo	finfo;
	Oid			typioparam;
	int			dims[MAXDIM];
	int			lbs[MAXDIM];
	int			ndims = 1;
	int			i;

	elemtypid = get_element_type(typid);
	if (!elemtypid)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("cannot convert Perl array to non-array type %s",
						format_type_be(typid))));

	astate = initArrayResult(elemtypid, CurrentMemoryContext, true);

	_sv_to_datum_finfo(elemtypid, &finfo, &typioparam);

	memset(dims, 0, sizeof(dims));
	dims[0] = av_len((AV *) SvRV(src)) + 1;

	array_to_datum_internal((AV *) SvRV(src), astate,
							&ndims, dims, 1,
							typid, elemtypid, typmod,
							&finfo, typioparam);

	/* ensure we get zero-D array for no inputs, as per PG convention */
	if (dims[0] <= 0)
		ndims = 0;

	for (i = 0; i < ndims; i++)
		lbs[i] = 1;

	return makeMdArrayResult(astate, ndims, dims, lbs,
							 CurrentMemoryContext, true);
}