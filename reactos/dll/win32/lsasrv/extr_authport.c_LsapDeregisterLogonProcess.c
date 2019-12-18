#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ConnectionHandle; int /*<<< orphan*/  ClientProcessHandle; int /*<<< orphan*/  Entry; } ;
typedef  int /*<<< orphan*/  PLSA_API_MSG ;
typedef  TYPE_1__* PLSAP_LOGON_CONTEXT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static NTSTATUS
LsapDeregisterLogonProcess(PLSA_API_MSG RequestMsg,
                           PLSAP_LOGON_CONTEXT LogonContext)
{
    TRACE("LsapDeregisterLogonProcess(%p %p)\n", RequestMsg, LogonContext);

    RemoveHeadList(&LogonContext->Entry);

    NtClose(LogonContext->ClientProcessHandle);
    NtClose(LogonContext->ConnectionHandle);

    RtlFreeHeap(RtlGetProcessHeap(), 0, LogonContext);

    return STATUS_SUCCESS;
}