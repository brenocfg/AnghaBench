#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  last_archived_timestamp; int /*<<< orphan*/  last_archived_wal; int /*<<< orphan*/  archived_count; int /*<<< orphan*/  last_failed_timestamp; int /*<<< orphan*/  last_failed_wal; int /*<<< orphan*/  failed_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  m_timestamp; int /*<<< orphan*/  m_xlog; scalar_t__ m_failed; } ;
typedef  TYPE_1__ PgStat_MsgArchiver ;

/* Variables and functions */
 TYPE_3__ archiverStats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
pgstat_recv_archiver(PgStat_MsgArchiver *msg, int len)
{
	if (msg->m_failed)
	{
		/* Failed archival attempt */
		++archiverStats.failed_count;
		memcpy(archiverStats.last_failed_wal, msg->m_xlog,
			   sizeof(archiverStats.last_failed_wal));
		archiverStats.last_failed_timestamp = msg->m_timestamp;
	}
	else
	{
		/* Successful archival operation */
		++archiverStats.archived_count;
		memcpy(archiverStats.last_archived_wal, msg->m_xlog,
			   sizeof(archiverStats.last_archived_wal));
		archiverStats.last_archived_timestamp = msg->m_timestamp;
	}
}