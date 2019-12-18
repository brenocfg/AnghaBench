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
 int /*<<< orphan*/  TermSrvMultiRdpReferences ; 
 int /*<<< orphan*/  kull_m_patch_genericProcessOrServiceFromBuild (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_ts_multirdp(int argc, wchar_t * argv[])
{
	kull_m_patch_genericProcessOrServiceFromBuild(TermSrvMultiRdpReferences, ARRAYSIZE(TermSrvMultiRdpReferences), L"TermService", L"termsrv.dll", TRUE);
	return STATUS_SUCCESS;
}