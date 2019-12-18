#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_3__ {int nkeys; int /*<<< orphan*/ * fk_attnums; int /*<<< orphan*/ * pk_attnums; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  TYPE_1__ RI_ConstraintInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  slot_getattr (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int*) ; 

__attribute__((used)) static void
ri_ExtractValues(Relation rel, TupleTableSlot *slot,
				 const RI_ConstraintInfo *riinfo, bool rel_is_pk,
				 Datum *vals, char *nulls)
{
	const int16 *attnums;
	bool		isnull;

	if (rel_is_pk)
		attnums = riinfo->pk_attnums;
	else
		attnums = riinfo->fk_attnums;

	for (int i = 0; i < riinfo->nkeys; i++)
	{
		vals[i] = slot_getattr(slot, attnums[i], &isnull);
		nulls[i] = isnull ? 'n' : ' ';
	}
}