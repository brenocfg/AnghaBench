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
struct TYPE_3__ {scalar_t__ PostOperation; scalar_t__ PreOperation; int /*<<< orphan*/  Handle; int /*<<< orphan*/  Operations; } ;
typedef  TYPE_1__* POBJECT_CALLBACK_ENTRY ;
typedef  int /*<<< orphan*/  PKIWI_BUFFER ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kkll_m_modules_fromAddr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kprintf (int /*<<< orphan*/ ,char*,...) ; 

NTSTATUS kkll_m_notify_desc_object_callback(POBJECT_CALLBACK_ENTRY pCallbackEntry, PKIWI_BUFFER outBuffer)
{
	NTSTATUS status = STATUS_SUCCESS;
	if(pCallbackEntry->PreOperation || pCallbackEntry->PostOperation)
	{
		status = kprintf(outBuffer, L"\t* Callback [type %u] - Handle 0x%p (@ 0x%p)\n", pCallbackEntry->Operations, pCallbackEntry->Handle, pCallbackEntry);
		if(NT_SUCCESS(status) && pCallbackEntry->PreOperation)
		{
			status = kprintf(outBuffer, L"\t\tPreOperation  : ");
			if(NT_SUCCESS(status))
				status = kkll_m_modules_fromAddr(outBuffer, pCallbackEntry->PreOperation);
		}
		if(NT_SUCCESS(status) && pCallbackEntry->PostOperation)
		{
			status = kprintf(outBuffer, L"\t\tPostOperation : ");
			if(NT_SUCCESS(status))
				status = kkll_m_modules_fromAddr(outBuffer, pCallbackEntry->PostOperation);
		}
	}
	return status;
}