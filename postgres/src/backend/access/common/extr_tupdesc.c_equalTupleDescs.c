#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_12__ {scalar_t__ has_not_null; scalar_t__ has_generated_stored; int num_defval; int num_check; TYPE_4__* check; TYPE_5__* missing; TYPE_6__* defval; } ;
typedef  TYPE_2__ TupleConstr ;
struct TYPE_16__ {scalar_t__ adnum; int /*<<< orphan*/  adbin; } ;
struct TYPE_15__ {scalar_t__ am_present; int /*<<< orphan*/  am_value; } ;
struct TYPE_14__ {scalar_t__ ccvalid; scalar_t__ ccnoinherit; int /*<<< orphan*/  ccbin; int /*<<< orphan*/  ccname; } ;
struct TYPE_13__ {scalar_t__ atttypid; scalar_t__ attstattarget; scalar_t__ attlen; scalar_t__ attndims; scalar_t__ atttypmod; scalar_t__ attbyval; scalar_t__ attstorage; scalar_t__ attalign; scalar_t__ attnotnull; scalar_t__ atthasdef; scalar_t__ attidentity; scalar_t__ attgenerated; scalar_t__ attisdropped; scalar_t__ attislocal; scalar_t__ attinhcount; scalar_t__ attcollation; int /*<<< orphan*/  attname; } ;
struct TYPE_11__ {int natts; scalar_t__ tdtypeid; TYPE_2__* constr; } ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_4__ ConstrCheck ;
typedef  TYPE_5__ AttrMissing ;
typedef  TYPE_6__ AttrDefault ;

/* Variables and functions */
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  datumIsEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
equalTupleDescs(TupleDesc tupdesc1, TupleDesc tupdesc2)
{
	int			i,
				j,
				n;

	if (tupdesc1->natts != tupdesc2->natts)
		return false;
	if (tupdesc1->tdtypeid != tupdesc2->tdtypeid)
		return false;

	for (i = 0; i < tupdesc1->natts; i++)
	{
		Form_pg_attribute attr1 = TupleDescAttr(tupdesc1, i);
		Form_pg_attribute attr2 = TupleDescAttr(tupdesc2, i);

		/*
		 * We do not need to check every single field here: we can disregard
		 * attrelid and attnum (which were used to place the row in the attrs
		 * array in the first place).  It might look like we could dispense
		 * with checking attlen/attbyval/attalign, since these are derived
		 * from atttypid; but in the case of dropped columns we must check
		 * them (since atttypid will be zero for all dropped columns) and in
		 * general it seems safer to check them always.
		 *
		 * attcacheoff must NOT be checked since it's possibly not set in both
		 * copies.
		 */
		if (strcmp(NameStr(attr1->attname), NameStr(attr2->attname)) != 0)
			return false;
		if (attr1->atttypid != attr2->atttypid)
			return false;
		if (attr1->attstattarget != attr2->attstattarget)
			return false;
		if (attr1->attlen != attr2->attlen)
			return false;
		if (attr1->attndims != attr2->attndims)
			return false;
		if (attr1->atttypmod != attr2->atttypmod)
			return false;
		if (attr1->attbyval != attr2->attbyval)
			return false;
		if (attr1->attstorage != attr2->attstorage)
			return false;
		if (attr1->attalign != attr2->attalign)
			return false;
		if (attr1->attnotnull != attr2->attnotnull)
			return false;
		if (attr1->atthasdef != attr2->atthasdef)
			return false;
		if (attr1->attidentity != attr2->attidentity)
			return false;
		if (attr1->attgenerated != attr2->attgenerated)
			return false;
		if (attr1->attisdropped != attr2->attisdropped)
			return false;
		if (attr1->attislocal != attr2->attislocal)
			return false;
		if (attr1->attinhcount != attr2->attinhcount)
			return false;
		if (attr1->attcollation != attr2->attcollation)
			return false;
		/* attacl, attoptions and attfdwoptions are not even present... */
	}

	if (tupdesc1->constr != NULL)
	{
		TupleConstr *constr1 = tupdesc1->constr;
		TupleConstr *constr2 = tupdesc2->constr;

		if (constr2 == NULL)
			return false;
		if (constr1->has_not_null != constr2->has_not_null)
			return false;
		if (constr1->has_generated_stored != constr2->has_generated_stored)
			return false;
		n = constr1->num_defval;
		if (n != (int) constr2->num_defval)
			return false;
		for (i = 0; i < n; i++)
		{
			AttrDefault *defval1 = constr1->defval + i;
			AttrDefault *defval2 = constr2->defval;

			/*
			 * We can't assume that the items are always read from the system
			 * catalogs in the same order; so use the adnum field to identify
			 * the matching item to compare.
			 */
			for (j = 0; j < n; defval2++, j++)
			{
				if (defval1->adnum == defval2->adnum)
					break;
			}
			if (j >= n)
				return false;
			if (strcmp(defval1->adbin, defval2->adbin) != 0)
				return false;
		}
		if (constr1->missing)
		{
			if (!constr2->missing)
				return false;
			for (i = 0; i < tupdesc1->natts; i++)
			{
				AttrMissing *missval1 = constr1->missing + i;
				AttrMissing *missval2 = constr2->missing + i;

				if (missval1->am_present != missval2->am_present)
					return false;
				if (missval1->am_present)
				{
					Form_pg_attribute missatt1 = TupleDescAttr(tupdesc1, i);

					if (!datumIsEqual(missval1->am_value, missval2->am_value,
									  missatt1->attbyval, missatt1->attlen))
						return false;
				}
			}
		}
		else if (constr2->missing)
			return false;
		n = constr1->num_check;
		if (n != (int) constr2->num_check)
			return false;
		for (i = 0; i < n; i++)
		{
			ConstrCheck *check1 = constr1->check + i;
			ConstrCheck *check2 = constr2->check;

			/*
			 * Similarly, don't assume that the checks are always read in the
			 * same order; match them up by name and contents. (The name
			 * *should* be unique, but...)
			 */
			for (j = 0; j < n; check2++, j++)
			{
				if (strcmp(check1->ccname, check2->ccname) == 0 &&
					strcmp(check1->ccbin, check2->ccbin) == 0 &&
					check1->ccvalid == check2->ccvalid &&
					check1->ccnoinherit == check2->ccnoinherit)
					break;
			}
			if (j >= n)
				return false;
		}
	}
	else if (tupdesc2->constr != NULL)
		return false;
	return true;
}