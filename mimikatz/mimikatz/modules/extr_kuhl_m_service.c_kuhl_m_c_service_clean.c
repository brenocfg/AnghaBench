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
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  SERVICE_STOP ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kuhl_m_service_CtrlHandler (int /*<<< orphan*/ ) ; 
 scalar_t__ m_ServiceStatusHandle ; 

NTSTATUS kuhl_m_c_service_clean()
{
	if(m_ServiceStatusHandle)
		kuhl_m_service_CtrlHandler(SERVICE_STOP);
	return STATUS_SUCCESS;
}