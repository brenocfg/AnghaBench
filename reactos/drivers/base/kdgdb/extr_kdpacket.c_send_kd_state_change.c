#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_7__ {int /*<<< orphan*/  ExceptionCode; } ;
struct TYPE_8__ {TYPE_1__ ExceptionRecord; } ;
struct TYPE_9__ {TYPE_2__ Exception; } ;
struct TYPE_10__ {int NewState; TYPE_3__ u; int /*<<< orphan*/  Thread; } ;
typedef  int /*<<< orphan*/  PETHREAD ;
typedef  TYPE_4__ DBGKD_ANY_WAIT_STATE_CHANGE ;

/* Variables and functions */
 TYPE_4__ CurrentStateChange ; 
#define  DbgKdExceptionStateChange 129 
#define  DbgKdLoadSymbolsStateChange 128 
 int /*<<< orphan*/  GetContextManipulateHandler ; 
 int /*<<< orphan*/  InException ; 
 int /*<<< orphan*/  KDDBGPRINT (char*,int,...) ; 
 int /*<<< orphan*/  KdpManipulateStateHandler ; 
 int /*<<< orphan*/  PsGetThreadId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PsGetThreadProcessId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gdb_dbg_pid ; 
 int /*<<< orphan*/  gdb_dbg_tid ; 
 int /*<<< orphan*/  gdb_send_exception () ; 
 int /*<<< orphan*/  handle_to_gdb_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_to_gdb_tid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void
send_kd_state_change(DBGKD_ANY_WAIT_STATE_CHANGE* StateChange)
{
    InException = TRUE;

    switch (StateChange->NewState)
    {
    case DbgKdLoadSymbolsStateChange:
    case DbgKdExceptionStateChange:
    {
        PETHREAD Thread = (PETHREAD)(ULONG_PTR)StateChange->Thread;
        /* Save current state for later GDB queries */
        CurrentStateChange = *StateChange;
        KDDBGPRINT("Exception 0x%08x in thread p%p.%p.\n",
            StateChange->u.Exception.ExceptionRecord.ExceptionCode,
            PsGetThreadProcessId(Thread),
            PsGetThreadId(Thread));
        /* Set the current debugged process/thread accordingly */
        gdb_dbg_tid = handle_to_gdb_tid(PsGetThreadId(Thread));
#if MONOPROCESS
        gdb_dbg_pid = 0;
#else
        gdb_dbg_pid = handle_to_gdb_pid(PsGetThreadProcessId(Thread));
#endif
        gdb_send_exception();
        /* Next receive call will ask for the context */
        KdpManipulateStateHandler = GetContextManipulateHandler;
        break;
    }
    default:
        KDDBGPRINT("Unknown StateChange %u.\n", StateChange->NewState);
        while (1);
    }
}