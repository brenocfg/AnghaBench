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
typedef  int /*<<< orphan*/  msg ;
struct TYPE_3__ {int /*<<< orphan*/  m_databaseid; int /*<<< orphan*/  m_hdr; } ;
typedef  TYPE_1__ PgStat_MsgDropdb ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  PGSTAT_MTYPE_DROPDB ; 
 scalar_t__ pgStatSock ; 
 int /*<<< orphan*/  pgstat_send (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pgstat_setheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pgstat_drop_database(Oid databaseid)
{
	PgStat_MsgDropdb msg;

	if (pgStatSock == PGINVALID_SOCKET)
		return;

	pgstat_setheader(&msg.m_hdr, PGSTAT_MTYPE_DROPDB);
	msg.m_databaseid = databaseid;
	pgstat_send(&msg, sizeof(msg));
}