#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_15__ {int num_defval; int num_check; TYPE_3__* check; TYPE_3__* missing; TYPE_3__* defval; int /*<<< orphan*/  has_generated_stored; int /*<<< orphan*/  has_not_null; } ;
typedef  TYPE_2__ TupleConstr ;
struct TYPE_16__ {int /*<<< orphan*/  ccnoinherit; int /*<<< orphan*/  ccvalid; void* ccbin; void* ccname; int /*<<< orphan*/  attlen; int /*<<< orphan*/  attbyval; int /*<<< orphan*/  am_value; scalar_t__ am_present; void* adbin; } ;
struct TYPE_14__ {int natts; int /*<<< orphan*/  tdtypmod; int /*<<< orphan*/  tdtypeid; TYPE_2__* constr; } ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  FormData_pg_attribute ;
typedef  TYPE_3__ ConstrCheck ;
typedef  TYPE_3__ AttrMissing ;
typedef  TYPE_3__ AttrDefault ;

/* Variables and functions */
 TYPE_1__* CreateTemplateTupleDesc (int) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  datumCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 scalar_t__ palloc (int) ; 
 scalar_t__ palloc0 (int) ; 
 void* pstrdup (void*) ; 

TupleDesc
CreateTupleDescCopyConstr(TupleDesc tupdesc)
{
	TupleDesc	desc;
	TupleConstr *constr = tupdesc->constr;
	int			i;

	desc = CreateTemplateTupleDesc(tupdesc->natts);

	/* Flat-copy the attribute array */
	memcpy(TupleDescAttr(desc, 0),
		   TupleDescAttr(tupdesc, 0),
		   desc->natts * sizeof(FormData_pg_attribute));

	/* Copy the TupleConstr data structure, if any */
	if (constr)
	{
		TupleConstr *cpy = (TupleConstr *) palloc0(sizeof(TupleConstr));

		cpy->has_not_null = constr->has_not_null;
		cpy->has_generated_stored = constr->has_generated_stored;

		if ((cpy->num_defval = constr->num_defval) > 0)
		{
			cpy->defval = (AttrDefault *) palloc(cpy->num_defval * sizeof(AttrDefault));
			memcpy(cpy->defval, constr->defval, cpy->num_defval * sizeof(AttrDefault));
			for (i = cpy->num_defval - 1; i >= 0; i--)
			{
				if (constr->defval[i].adbin)
					cpy->defval[i].adbin = pstrdup(constr->defval[i].adbin);
			}
		}

		if (constr->missing)
		{
			cpy->missing = (AttrMissing *) palloc(tupdesc->natts * sizeof(AttrMissing));
			memcpy(cpy->missing, constr->missing, tupdesc->natts * sizeof(AttrMissing));
			for (i = tupdesc->natts - 1; i >= 0; i--)
			{
				if (constr->missing[i].am_present)
				{
					Form_pg_attribute attr = TupleDescAttr(tupdesc, i);

					cpy->missing[i].am_value = datumCopy(constr->missing[i].am_value,
														 attr->attbyval,
														 attr->attlen);
				}
			}
		}

		if ((cpy->num_check = constr->num_check) > 0)
		{
			cpy->check = (ConstrCheck *) palloc(cpy->num_check * sizeof(ConstrCheck));
			memcpy(cpy->check, constr->check, cpy->num_check * sizeof(ConstrCheck));
			for (i = cpy->num_check - 1; i >= 0; i--)
			{
				if (constr->check[i].ccname)
					cpy->check[i].ccname = pstrdup(constr->check[i].ccname);
				if (constr->check[i].ccbin)
					cpy->check[i].ccbin = pstrdup(constr->check[i].ccbin);
				cpy->check[i].ccvalid = constr->check[i].ccvalid;
				cpy->check[i].ccnoinherit = constr->check[i].ccnoinherit;
			}
		}

		desc->constr = cpy;
	}

	/* We can copy the tuple type identification, too */
	desc->tdtypeid = tupdesc->tdtypeid;
	desc->tdtypmod = tupdesc->tdtypmod;

	return desc;
}