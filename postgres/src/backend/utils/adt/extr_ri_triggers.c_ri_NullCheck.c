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
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_3__ {int nkeys; int /*<<< orphan*/ * fk_attnums; int /*<<< orphan*/ * pk_attnums; } ;
typedef  TYPE_1__ RI_ConstraintInfo ;

/* Variables and functions */
 int RI_KEYS_ALL_NULL ; 
 int RI_KEYS_NONE_NULL ; 
 int RI_KEYS_SOME_NULL ; 
 scalar_t__ slot_attisnull (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int
ri_NullCheck(TupleDesc tupDesc,
			 TupleTableSlot *slot,
			 const RI_ConstraintInfo *riinfo, bool rel_is_pk)
{
	const int16 *attnums;
	bool		allnull = true;
	bool		nonenull = true;

	if (rel_is_pk)
		attnums = riinfo->pk_attnums;
	else
		attnums = riinfo->fk_attnums;

	for (int i = 0; i < riinfo->nkeys; i++)
	{
		if (slot_attisnull(slot, attnums[i]))
			nonenull = false;
		else
			allnull = false;
	}

	if (allnull)
		return RI_KEYS_ALL_NULL;

	if (nonenull)
		return RI_KEYS_NONE_NULL;

	return RI_KEYS_SOME_NULL;
}