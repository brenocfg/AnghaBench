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
typedef  int WaitEventActivity ;

/* Variables and functions */
#define  WAIT_EVENT_ARCHIVER_MAIN 141 
#define  WAIT_EVENT_AUTOVACUUM_MAIN 140 
#define  WAIT_EVENT_BGWRITER_HIBERNATE 139 
#define  WAIT_EVENT_BGWRITER_MAIN 138 
#define  WAIT_EVENT_CHECKPOINTER_MAIN 137 
#define  WAIT_EVENT_LOGICAL_APPLY_MAIN 136 
#define  WAIT_EVENT_LOGICAL_LAUNCHER_MAIN 135 
#define  WAIT_EVENT_PGSTAT_MAIN 134 
#define  WAIT_EVENT_RECOVERY_WAL_ALL 133 
#define  WAIT_EVENT_RECOVERY_WAL_STREAM 132 
#define  WAIT_EVENT_SYSLOGGER_MAIN 131 
#define  WAIT_EVENT_WAL_RECEIVER_MAIN 130 
#define  WAIT_EVENT_WAL_SENDER_MAIN 129 
#define  WAIT_EVENT_WAL_WRITER_MAIN 128 

__attribute__((used)) static const char *
pgstat_get_wait_activity(WaitEventActivity w)
{
	const char *event_name = "unknown wait event";

	switch (w)
	{
		case WAIT_EVENT_ARCHIVER_MAIN:
			event_name = "ArchiverMain";
			break;
		case WAIT_EVENT_AUTOVACUUM_MAIN:
			event_name = "AutoVacuumMain";
			break;
		case WAIT_EVENT_BGWRITER_HIBERNATE:
			event_name = "BgWriterHibernate";
			break;
		case WAIT_EVENT_BGWRITER_MAIN:
			event_name = "BgWriterMain";
			break;
		case WAIT_EVENT_CHECKPOINTER_MAIN:
			event_name = "CheckpointerMain";
			break;
		case WAIT_EVENT_LOGICAL_APPLY_MAIN:
			event_name = "LogicalApplyMain";
			break;
		case WAIT_EVENT_LOGICAL_LAUNCHER_MAIN:
			event_name = "LogicalLauncherMain";
			break;
		case WAIT_EVENT_PGSTAT_MAIN:
			event_name = "PgStatMain";
			break;
		case WAIT_EVENT_RECOVERY_WAL_ALL:
			event_name = "RecoveryWalAll";
			break;
		case WAIT_EVENT_RECOVERY_WAL_STREAM:
			event_name = "RecoveryWalStream";
			break;
		case WAIT_EVENT_SYSLOGGER_MAIN:
			event_name = "SysLoggerMain";
			break;
		case WAIT_EVENT_WAL_RECEIVER_MAIN:
			event_name = "WalReceiverMain";
			break;
		case WAIT_EVENT_WAL_SENDER_MAIN:
			event_name = "WalSenderMain";
			break;
		case WAIT_EVENT_WAL_WRITER_MAIN:
			event_name = "WalWriterMain";
			break;
			/* no default case, so that compiler will warn */
	}

	return event_name;
}