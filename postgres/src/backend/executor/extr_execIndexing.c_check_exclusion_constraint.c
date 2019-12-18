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
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ItemPointer ;
typedef  int /*<<< orphan*/  IndexInfo ;
typedef  int /*<<< orphan*/  EState ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  CEOUC_WAIT ; 
 int /*<<< orphan*/  check_exclusion_or_unique_constraint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
check_exclusion_constraint(Relation heap, Relation index,
						   IndexInfo *indexInfo,
						   ItemPointer tupleid,
						   Datum *values, bool *isnull,
						   EState *estate, bool newIndex)
{
	(void) check_exclusion_or_unique_constraint(heap, index, indexInfo, tupleid,
												values, isnull,
												estate, newIndex,
												CEOUC_WAIT, false, NULL);
}