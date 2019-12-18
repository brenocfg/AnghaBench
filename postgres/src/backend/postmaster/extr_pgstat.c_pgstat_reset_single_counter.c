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
struct TYPE_3__ {int /*<<< orphan*/  m_objectid; int /*<<< orphan*/  m_resettype; int /*<<< orphan*/  m_databaseid; int /*<<< orphan*/  m_hdr; } ;
typedef  int /*<<< orphan*/  PgStat_Single_Reset_Type ;
typedef  TYPE_1__ PgStat_MsgResetsinglecounter ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  MyDatabaseId ; 
 scalar_t__ PGINVALID_SOCKET ; 
 int /*<<< orphan*/  PGSTAT_MTYPE_RESETSINGLECOUNTER ; 
 scalar_t__ pgStatSock ; 
 int /*<<< orphan*/  pgstat_send (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pgstat_setheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pgstat_reset_single_counter(Oid objoid, PgStat_Single_Reset_Type type)
{
	PgStat_MsgResetsinglecounter msg;

	if (pgStatSock == PGINVALID_SOCKET)
		return;

	pgstat_setheader(&msg.m_hdr, PGSTAT_MTYPE_RESETSINGLECOUNTER);
	msg.m_databaseid = MyDatabaseId;
	msg.m_resettype = type;
	msg.m_objectid = objoid;

	pgstat_send(&msg, sizeof(msg));
}