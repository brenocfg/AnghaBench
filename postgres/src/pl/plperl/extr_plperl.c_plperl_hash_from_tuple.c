#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_12__ {TYPE_1__* prodesc; } ;
struct TYPE_11__ {int /*<<< orphan*/  atttypid; int /*<<< orphan*/  attname; scalar_t__ attgenerated; scalar_t__ attisdropped; } ;
struct TYPE_10__ {int natts; } ;
struct TYPE_9__ {int /*<<< orphan*/  trftypes; int /*<<< orphan*/  lang_oid; } ;
typedef  int /*<<< orphan*/  SV ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HV ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetPointer (int /*<<< orphan*/ ) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 char* OidOutputFunctionCall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/ * cstr2sv (char*) ; 
 TYPE_6__* current_call_data ; 
 int /*<<< orphan*/  dTHX ; 
 int /*<<< orphan*/  getTypeOutputInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_base_element_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_transform_fromsql (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int,TYPE_2__*,int*) ; 
 int /*<<< orphan*/  hv_ksplit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hv_store_string (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newHV () ; 
 int /*<<< orphan*/ * newRV_noinc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * newSV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int /*<<< orphan*/ * plperl_hash_from_datum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * plperl_ref_from_pg_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ type_is_rowtype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static SV  *
plperl_hash_from_tuple(HeapTuple tuple, TupleDesc tupdesc, bool include_generated)
{
	dTHX;
	HV		   *hv;
	int			i;

	/* since this function recurses, it could be driven to stack overflow */
	check_stack_depth();

	hv = newHV();
	hv_ksplit(hv, tupdesc->natts);	/* pre-grow the hash */

	for (i = 0; i < tupdesc->natts; i++)
	{
		Datum		attr;
		bool		isnull,
					typisvarlena;
		char	   *attname;
		Oid			typoutput;
		Form_pg_attribute att = TupleDescAttr(tupdesc, i);

		if (att->attisdropped)
			continue;

		if (att->attgenerated)
		{
			/* don't include unless requested */
			if (!include_generated)
				continue;
		}

		attname = NameStr(att->attname);
		attr = heap_getattr(tuple, i + 1, tupdesc, &isnull);

		if (isnull)
		{
			/*
			 * Store (attname => undef) and move on.  Note we can't use
			 * &PL_sv_undef here; see "AVs, HVs and undefined values" in
			 * perlguts for an explanation.
			 */
			hv_store_string(hv, attname, newSV(0));
			continue;
		}

		if (type_is_rowtype(att->atttypid))
		{
			SV		   *sv = plperl_hash_from_datum(attr);

			hv_store_string(hv, attname, sv);
		}
		else
		{
			SV		   *sv;
			Oid			funcid;

			if (OidIsValid(get_base_element_type(att->atttypid)))
				sv = plperl_ref_from_pg_array(attr, att->atttypid);
			else if ((funcid = get_transform_fromsql(att->atttypid, current_call_data->prodesc->lang_oid, current_call_data->prodesc->trftypes)))
				sv = (SV *) DatumGetPointer(OidFunctionCall1(funcid, attr));
			else
			{
				char	   *outputstr;

				/* XXX should have a way to cache these lookups */
				getTypeOutputInfo(att->atttypid, &typoutput, &typisvarlena);

				outputstr = OidOutputFunctionCall(typoutput, attr);
				sv = cstr2sv(outputstr);
				pfree(outputstr);
			}

			hv_store_string(hv, attname, sv);
		}
	}
	return newRV_noinc((SV *) hv);
}