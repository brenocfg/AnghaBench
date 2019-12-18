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
struct TYPE_3__ {int m_failed; int /*<<< orphan*/  m_timestamp; int /*<<< orphan*/  m_xlog; int /*<<< orphan*/  m_hdr; } ;
typedef  TYPE_1__ PgStat_MsgArchiver ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  PGSTAT_MTYPE_ARCHIVER ; 
 int /*<<< orphan*/  StrNCpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  pgstat_send (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pgstat_setheader (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pgstat_send_archiver(const char *xlog, bool failed)
{
	PgStat_MsgArchiver msg;

	/*
	 * Prepare and send the message
	 */
	pgstat_setheader(&msg.m_hdr, PGSTAT_MTYPE_ARCHIVER);
	msg.m_failed = failed;
	StrNCpy(msg.m_xlog, xlog, sizeof(msg.m_xlog));
	msg.m_timestamp = GetCurrentTimestamp();
	pgstat_send(&msg, sizeof(msg));
}