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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_5__ {scalar_t__ dwCheckPoint; scalar_t__ dwCurrentState; } ;
struct TYPE_4__ {TYPE_3__ servStatus; int /*<<< orphan*/  hStatus; } ;
typedef  TYPE_1__* PSERVICEINFO ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  LOG_ALL ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetServiceStatus (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  _snwprintf (char*,int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static VOID
UpdateStatus(PSERVICEINFO pServInfo,
             DWORD NewStatus,
             DWORD Check)
{
    WCHAR szSet[50];

    if (Check > 0)
        pServInfo->servStatus.dwCheckPoint += Check;
    else
        pServInfo->servStatus.dwCheckPoint = Check;

    if (NewStatus > 0)
        pServInfo->servStatus.dwCurrentState = NewStatus;

    _snwprintf(szSet,
               49,
               L"Service state 0x%lx, CheckPoint %lu",
               pServInfo->servStatus.dwCurrentState,
               pServInfo->servStatus.dwCheckPoint);
    LogEvent(szSet, 0, 0, LOG_FILE);

    if (!SetServiceStatus(pServInfo->hStatus, &pServInfo->servStatus))
        LogEvent(L"Cannot set service status", GetLastError(), 0, LOG_ALL);
}