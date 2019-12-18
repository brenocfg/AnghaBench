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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kull_m_patch_genericProcessOrServiceFromBuild (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncRouteMonitorReferences ; 

NTSTATUS kuhl_m_misc_ncroutemon(int argc, wchar_t * argv[])
{
	kull_m_patch_genericProcessOrServiceFromBuild(ncRouteMonitorReferences, ARRAYSIZE(ncRouteMonitorReferences), L"dsNcService", NULL, TRUE);
	return STATUS_SUCCESS;
}