#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int m_reason; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/  n_conflict_startup_deadlock; int /*<<< orphan*/  n_conflict_bufferpin; int /*<<< orphan*/  n_conflict_snapshot; int /*<<< orphan*/  n_conflict_lock; int /*<<< orphan*/  n_conflict_tablespace; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgRecoveryConflict ;

/* Variables and functions */
#define  PROCSIG_RECOVERY_CONFLICT_BUFFERPIN 133 
#define  PROCSIG_RECOVERY_CONFLICT_DATABASE 132 
#define  PROCSIG_RECOVERY_CONFLICT_LOCK 131 
#define  PROCSIG_RECOVERY_CONFLICT_SNAPSHOT 130 
#define  PROCSIG_RECOVERY_CONFLICT_STARTUP_DEADLOCK 129 
#define  PROCSIG_RECOVERY_CONFLICT_TABLESPACE 128 
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_recoveryconflict(PgStat_MsgRecoveryConflict *msg, int len)
{
	PgStat_StatDBEntry *dbentry;

	dbentry = pgstat_get_db_entry(msg->m_databaseid, true);

	switch (msg->m_reason)
	{
		case PROCSIG_RECOVERY_CONFLICT_DATABASE:

			/*
			 * Since we drop the information about the database as soon as it
			 * replicates, there is no point in counting these conflicts.
			 */
			break;
		case PROCSIG_RECOVERY_CONFLICT_TABLESPACE:
			dbentry->n_conflict_tablespace++;
			break;
		case PROCSIG_RECOVERY_CONFLICT_LOCK:
			dbentry->n_conflict_lock++;
			break;
		case PROCSIG_RECOVERY_CONFLICT_SNAPSHOT:
			dbentry->n_conflict_snapshot++;
			break;
		case PROCSIG_RECOVERY_CONFLICT_BUFFERPIN:
			dbentry->n_conflict_bufferpin++;
			break;
		case PROCSIG_RECOVERY_CONFLICT_STARTUP_DEADLOCK:
			dbentry->n_conflict_startup_deadlock++;
			break;
	}
}