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
struct TYPE_6__ {int /*<<< orphan*/  m_failure_time; scalar_t__ m_failurecount; int /*<<< orphan*/  m_databaseid; } ;
struct TYPE_5__ {int /*<<< orphan*/  last_checksum_failure; int /*<<< orphan*/  n_checksum_failures; } ;
typedef  TYPE_1__ PgStat_StatDBEntry ;
typedef  TYPE_2__ PgStat_MsgChecksumFailure ;

/* Variables and functions */
 TYPE_1__* pgstat_get_db_entry (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_checksum_failure(PgStat_MsgChecksumFailure *msg, int len)
{
	PgStat_StatDBEntry *dbentry;

	dbentry = pgstat_get_db_entry(msg->m_databaseid, true);

	dbentry->n_checksum_failures += msg->m_failurecount;
	dbentry->last_checksum_failure = msg->m_failure_time;
}