#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16 ;
struct TYPE_9__ {int /*<<< orphan*/  tts_tupleDescriptor; } ;
typedef  TYPE_1__ TupleTableSlot ;
struct TYPE_11__ {int /*<<< orphan*/  attlen; int /*<<< orphan*/  attbyval; } ;
struct TYPE_10__ {int nkeys; int /*<<< orphan*/ * ff_eq_oprs; scalar_t__* fk_attnums; scalar_t__* pk_attnums; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_2__ RI_ConstraintInfo ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  RIAttType (int /*<<< orphan*/ ,scalar_t__ const) ; 
 TYPE_3__* TupleDescAttr (int /*<<< orphan*/ ,scalar_t__ const) ; 
 int /*<<< orphan*/  datum_image_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ri_AttributesEqual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slot_getattr (TYPE_1__*,scalar_t__ const,int*) ; 

__attribute__((used)) static bool
ri_KeysEqual(Relation rel, TupleTableSlot *oldslot, TupleTableSlot *newslot,
			 const RI_ConstraintInfo *riinfo, bool rel_is_pk)
{
	const int16 *attnums;

	if (rel_is_pk)
		attnums = riinfo->pk_attnums;
	else
		attnums = riinfo->fk_attnums;

	/* XXX: could be worthwhile to fetch all necessary attrs at once */
	for (int i = 0; i < riinfo->nkeys; i++)
	{
		Datum		oldvalue;
		Datum		newvalue;
		bool		isnull;

		/*
		 * Get one attribute's oldvalue. If it is NULL - they're not equal.
		 */
		oldvalue = slot_getattr(oldslot, attnums[i], &isnull);
		if (isnull)
			return false;

		/*
		 * Get one attribute's newvalue. If it is NULL - they're not equal.
		 */
		newvalue = slot_getattr(newslot, attnums[i], &isnull);
		if (isnull)
			return false;

		if (rel_is_pk)
		{
			/*
			 * If we are looking at the PK table, then do a bytewise
			 * comparison.  We must propagate PK changes if the value is
			 * changed to one that "looks" different but would compare as
			 * equal using the equality operator.  This only makes a
			 * difference for ON UPDATE CASCADE, but for consistency we treat
			 * all changes to the PK the same.
			 */
			Form_pg_attribute att = TupleDescAttr(oldslot->tts_tupleDescriptor, attnums[i] - 1);

			if (!datum_image_eq(oldvalue, newvalue, att->attbyval, att->attlen))
				return false;
		}
		else
		{
			/*
			 * For the FK table, compare with the appropriate equality
			 * operator.  Changes that compare equal will still satisfy the
			 * constraint after the update.
			 */
			if (!ri_AttributesEqual(riinfo->ff_eq_oprs[i], RIAttType(rel, attnums[i]),
									oldvalue, newvalue))
				return false;
		}
	}

	return true;
}