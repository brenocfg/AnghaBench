#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int DaysInterval; } ;
struct TYPE_12__ {TYPE_1__ Daily; } ;
struct TYPE_16__ {int cbTriggerSize; TYPE_2__ Type; int /*<<< orphan*/  TriggerType; int /*<<< orphan*/  rgFlags; int /*<<< orphan*/  wStartMinute; int /*<<< orphan*/  wStartHour; int /*<<< orphan*/  wBeginDay; int /*<<< orphan*/  wBeginMonth; int /*<<< orphan*/  wBeginYear; } ;
struct TYPE_13__ {int ref; TYPE_5__ ITaskTrigger_iface; TYPE_6__ triggerCond; } ;
typedef  TYPE_3__ TaskTriggerImpl ;
struct TYPE_14__ {int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wHour; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  int /*<<< orphan*/  TASK_TRIGGER ;
typedef  TYPE_4__ SYSTEMTIME ;
typedef  TYPE_5__* LPVOID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetLocalTime (TYPE_4__*) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InterlockedIncrement (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MSTASK_ITaskTriggerVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TASK_TIME_TRIGGER_DAILY ; 
 int /*<<< orphan*/  TASK_TRIGGER_FLAG_DISABLED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_5__**) ; 
 int /*<<< orphan*/  dll_ref ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 

HRESULT TaskTriggerConstructor(LPVOID *ppObj)
{
    TaskTriggerImpl *This;
    SYSTEMTIME time;
    TRACE("(%p)\n", ppObj);

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This)
        return E_OUTOFMEMORY;

    This->ITaskTrigger_iface.lpVtbl = &MSTASK_ITaskTriggerVtbl;
    This->ref = 1;

    /* Most fields of triggerCond default to zero.  Initialize other
     * fields to default values. */
    memset(&This->triggerCond, 0, sizeof(TASK_TRIGGER));
    GetLocalTime(&time);
    This->triggerCond.cbTriggerSize = sizeof(This->triggerCond);
    This->triggerCond.wBeginYear = time.wYear;
    This->triggerCond.wBeginMonth = time.wMonth;
    This->triggerCond.wBeginDay = time.wDay;
    This->triggerCond.wStartHour = time.wHour;
    This->triggerCond.wStartMinute = time.wMinute;
    This->triggerCond.rgFlags = TASK_TRIGGER_FLAG_DISABLED;
    This->triggerCond.TriggerType = TASK_TIME_TRIGGER_DAILY,
    This->triggerCond.Type.Daily.DaysInterval = 1;

    *ppObj = &This->ITaskTrigger_iface;
    InterlockedIncrement(&dll_ref);
    return S_OK;
}