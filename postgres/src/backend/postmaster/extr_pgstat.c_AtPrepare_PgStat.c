#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  t_truncated; int /*<<< orphan*/  t_shared; int /*<<< orphan*/  t_id; int /*<<< orphan*/  deleted_pre_trunc; int /*<<< orphan*/  updated_pre_trunc; int /*<<< orphan*/  inserted_pre_trunc; int /*<<< orphan*/  tuples_deleted; int /*<<< orphan*/  tuples_updated; int /*<<< orphan*/  tuples_inserted; } ;
typedef  TYPE_1__ TwoPhasePgStatRecord ;
struct TYPE_10__ {int nest_level; TYPE_2__* first; int /*<<< orphan*/ * prev; } ;
struct TYPE_9__ {int /*<<< orphan*/  t_shared; int /*<<< orphan*/  t_id; TYPE_2__* trans; } ;
struct TYPE_8__ {int nest_level; int /*<<< orphan*/  truncated; int /*<<< orphan*/  deleted_pre_trunc; int /*<<< orphan*/  updated_pre_trunc; int /*<<< orphan*/  inserted_pre_trunc; int /*<<< orphan*/  tuples_deleted; int /*<<< orphan*/  tuples_updated; int /*<<< orphan*/  tuples_inserted; TYPE_3__* parent; int /*<<< orphan*/ * upper; struct TYPE_8__* next; } ;
typedef  TYPE_2__ PgStat_TableXactStatus ;
typedef  TYPE_3__ PgStat_TableStatus ;
typedef  TYPE_4__ PgStat_SubXactStatus ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  RegisterTwoPhaseRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  TWOPHASE_RM_PGSTAT_ID ; 
 TYPE_4__* pgStatXactStack ; 

void
AtPrepare_PgStat(void)
{
	PgStat_SubXactStatus *xact_state;

	xact_state = pgStatXactStack;
	if (xact_state != NULL)
	{
		PgStat_TableXactStatus *trans;

		Assert(xact_state->nest_level == 1);
		Assert(xact_state->prev == NULL);
		for (trans = xact_state->first; trans != NULL; trans = trans->next)
		{
			PgStat_TableStatus *tabstat;
			TwoPhasePgStatRecord record;

			Assert(trans->nest_level == 1);
			Assert(trans->upper == NULL);
			tabstat = trans->parent;
			Assert(tabstat->trans == trans);

			record.tuples_inserted = trans->tuples_inserted;
			record.tuples_updated = trans->tuples_updated;
			record.tuples_deleted = trans->tuples_deleted;
			record.inserted_pre_trunc = trans->inserted_pre_trunc;
			record.updated_pre_trunc = trans->updated_pre_trunc;
			record.deleted_pre_trunc = trans->deleted_pre_trunc;
			record.t_id = tabstat->t_id;
			record.t_shared = tabstat->t_shared;
			record.t_truncated = trans->truncated;

			RegisterTwoPhaseRecord(TWOPHASE_RM_PGSTAT_ID, 0,
								   &record, sizeof(TwoPhasePgStatRecord));
		}
	}
}