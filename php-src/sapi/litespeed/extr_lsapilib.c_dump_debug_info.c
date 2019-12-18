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
struct TYPE_3__ {int m_pid; scalar_t__ m_tmStart; scalar_t__ m_tmLastCheckPoint; scalar_t__ m_tmReqBegin; int /*<<< orphan*/  m_iReqCounter; } ;
typedef  TYPE_1__ lsapi_child_status ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsapi_log (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ s_pid_dump_debug_info ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 int system (char*) ; 

__attribute__((used)) static void dump_debug_info( lsapi_child_status * pStatus, long tmCur )
{
    char achCmd[1024];
    if ( s_pid_dump_debug_info )
    {
        if ( kill( s_pid_dump_debug_info, 0 ) == 0 )
            return;
    }

    lsapi_log("Possible runaway process, PPID: %d, PID: %d, "
             "reqCount: %d, process time: %ld, checkpoint time: %ld, start "
             "time: %ld\n", getpid(), pStatus->m_pid,
             pStatus->m_iReqCounter, tmCur - pStatus->m_tmReqBegin,
             tmCur - pStatus->m_tmLastCheckPoint, tmCur - pStatus->m_tmStart );

    s_pid_dump_debug_info = fork();
    if (s_pid_dump_debug_info == 0)
    {
        snprintf( achCmd, 1024, "gdb --batch -ex \"attach %d\" -ex \"set height 0\" "
                "-ex \"bt\" >&2;PATH=$PATH:/usr/sbin lsof -p %d >&2",
                pStatus->m_pid, pStatus->m_pid );
        if ( system( achCmd ) == -1 )
            perror( "system()" );
        exit( 0 );
    }
}