#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ndims; int* nelems; int /*<<< orphan*/  nulls; int /*<<< orphan*/  elements; int /*<<< orphan*/  elem_is_rowtype; int /*<<< orphan*/  proc; int /*<<< orphan*/  transform_proc; } ;
typedef  TYPE_2__ plperl_array_info ;
typedef  int /*<<< orphan*/  int16 ;
struct TYPE_8__ {TYPE_1__* prodesc; } ;
struct TYPE_6__ {int /*<<< orphan*/  trftypes; int /*<<< orphan*/  lang_oid; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HV ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int* ARR_DIMS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
 int ARR_NDIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOFunc_output ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 TYPE_5__* current_call_data ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_transform_fromsql (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_type_io_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gv_stashpv (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_store (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ newAV () ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/ * newRV_noinc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newSVuv (int /*<<< orphan*/ ) ; 
 int* palloc (int) ; 
 TYPE_2__* palloc0 (int) ; 
 int /*<<< orphan*/ * split_array (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sv_bless (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_is_rowtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SV  *
plperl_ref_from_pg_array(Datum arg, Oid typid)
{
	dTHX;
	ArrayType  *ar = DatumGetArrayTypeP(arg);
	Oid			elementtype = ARR_ELEMTYPE(ar);
	int16		typlen;
	bool		typbyval;
	char		typalign,
				typdelim;
	Oid			typioparam;
	Oid			typoutputfunc;
	Oid			transform_funcid;
	int			i,
				nitems,
			   *dims;
	plperl_array_info *info;
	SV		   *av;
	HV		   *hv;

	/*
	 * Currently we make no effort to cache any of the stuff we look up here,
	 * which is bad.
	 */
	info = palloc0(sizeof(plperl_array_info));

	/* get element type information, including output conversion function */
	get_type_io_data(elementtype, IOFunc_output,
					 &typlen, &typbyval, &typalign,
					 &typdelim, &typioparam, &typoutputfunc);

	/* Check for a transform function */
	transform_funcid = get_transform_fromsql(elementtype,
											 current_call_data->prodesc->lang_oid,
											 current_call_data->prodesc->trftypes);

	/* Look up transform or output function as appropriate */
	if (OidIsValid(transform_funcid))
		fmgr_info(transform_funcid, &info->transform_proc);
	else
		fmgr_info(typoutputfunc, &info->proc);

	info->elem_is_rowtype = type_is_rowtype(elementtype);

	/* Get the number and bounds of array dimensions */
	info->ndims = ARR_NDIM(ar);
	dims = ARR_DIMS(ar);

	/* No dimensions? Return an empty array */
	if (info->ndims == 0)
	{
		av = newRV_noinc((SV *) newAV());
	}
	else
	{
		deconstruct_array(ar, elementtype, typlen, typbyval,
						  typalign, &info->elements, &info->nulls,
						  &nitems);

		/* Get total number of elements in each dimension */
		info->nelems = palloc(sizeof(int) * info->ndims);
		info->nelems[0] = nitems;
		for (i = 1; i < info->ndims; i++)
			info->nelems[i] = info->nelems[i - 1] / dims[i - 1];

		av = split_array(info, 0, nitems, 0);
	}

	hv = newHV();
	(void) hv_store(hv, "array", 5, av, 0);
	(void) hv_store(hv, "typeoid", 7, newSVuv(typid), 0);

	return sv_bless(newRV_noinc((SV *) hv),
					gv_stashpv("PostgreSQL::InServer::ARRAY", 0));
}