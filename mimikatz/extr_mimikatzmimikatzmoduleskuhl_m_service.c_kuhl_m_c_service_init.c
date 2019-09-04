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
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/ * hKiwiEventRunning ; 
 int /*<<< orphan*/ * m_ServiceStatusHandle ; 

NTSTATUS kuhl_m_c_service_init()
{
	m_ServiceStatusHandle = NULL;
	hKiwiEventRunning = NULL;
	return STATUS_SUCCESS;
}