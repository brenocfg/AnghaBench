#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_6__ {scalar_t__ tuples_deleted; scalar_t__ tuples_updated; scalar_t__ tuples_inserted; scalar_t__ t_truncated; int /*<<< orphan*/  t_shared; int /*<<< orphan*/  t_id; } ;
typedef  TYPE_2__ TwoPhasePgStatRecord ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_5__ {int /*<<< orphan*/  t_changed_tuples; scalar_t__ t_delta_dead_tuples; scalar_t__ t_delta_live_tuples; scalar_t__ t_truncated; int /*<<< orphan*/  t_tuples_deleted; int /*<<< orphan*/  t_tuples_updated; int /*<<< orphan*/  t_tuples_inserted; } ;
struct TYPE_7__ {TYPE_1__ t_counts; } ;
typedef  TYPE_3__ PgStat_TableStatus ;

/* Variables and functions */
 TYPE_3__* get_tabstat_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pgstat_twophase_postcommit(TransactionId xid, uint16 info,
						   void *recdata, uint32 len)
{
	TwoPhasePgStatRecord *rec = (TwoPhasePgStatRecord *) recdata;
	PgStat_TableStatus *pgstat_info;

	/* Find or create a tabstat entry for the rel */
	pgstat_info = get_tabstat_entry(rec->t_id, rec->t_shared);

	/* Same math as in AtEOXact_PgStat, commit case */
	pgstat_info->t_counts.t_tuples_inserted += rec->tuples_inserted;
	pgstat_info->t_counts.t_tuples_updated += rec->tuples_updated;
	pgstat_info->t_counts.t_tuples_deleted += rec->tuples_deleted;
	pgstat_info->t_counts.t_truncated = rec->t_truncated;
	if (rec->t_truncated)
	{
		/* forget live/dead stats seen by backend thus far */
		pgstat_info->t_counts.t_delta_live_tuples = 0;
		pgstat_info->t_counts.t_delta_dead_tuples = 0;
	}
	pgstat_info->t_counts.t_delta_live_tuples +=
		rec->tuples_inserted - rec->tuples_deleted;
	pgstat_info->t_counts.t_delta_dead_tuples +=
		rec->tuples_updated + rec->tuples_deleted;
	pgstat_info->t_counts.t_changed_tuples +=
		rec->tuples_inserted + rec->tuples_updated +
		rec->tuples_deleted;
}