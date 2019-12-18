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
 int /*<<< orphan*/  kuhl_m_dpapi_oe_credentials_delete () ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_domainkeys_delete () ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_masterkeys_delete () ; 

NTSTATUS kuhl_m_dpapi_oe_clean()
{
	kuhl_m_dpapi_oe_credentials_delete();
	kuhl_m_dpapi_oe_masterkeys_delete();
	kuhl_m_dpapi_oe_domainkeys_delete();
	return STATUS_SUCCESS;
}