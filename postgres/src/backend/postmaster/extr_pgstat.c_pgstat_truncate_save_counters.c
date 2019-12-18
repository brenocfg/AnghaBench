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
struct TYPE_3__ {int truncated; int /*<<< orphan*/  tuples_deleted; int /*<<< orphan*/  deleted_pre_trunc; int /*<<< orphan*/  tuples_updated; int /*<<< orphan*/  updated_pre_trunc; int /*<<< orphan*/  tuples_inserted; int /*<<< orphan*/  inserted_pre_trunc; } ;
typedef  TYPE_1__ PgStat_TableXactStatus ;

/* Variables and functions */

__attribute__((used)) static void
pgstat_truncate_save_counters(PgStat_TableXactStatus *trans)
{
	if (!trans->truncated)
	{
		trans->inserted_pre_trunc = trans->tuples_inserted;
		trans->updated_pre_trunc = trans->tuples_updated;
		trans->deleted_pre_trunc = trans->tuples_deleted;
		trans->truncated = true;
	}
}