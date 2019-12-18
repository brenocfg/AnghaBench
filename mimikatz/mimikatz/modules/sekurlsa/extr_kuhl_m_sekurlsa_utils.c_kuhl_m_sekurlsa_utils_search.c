#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ BuildNumber; } ;
struct TYPE_6__ {TYPE_1__ osContext; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PKUHL_M_SEKURLSA_LIB ;
typedef  TYPE_2__* PKUHL_M_SEKURLSA_CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ KULL_M_WIN_BUILD_2K3 ; 
 int /*<<< orphan*/  LogonSessionList ; 
 int /*<<< orphan*/  LogonSessionListCount ; 
 int /*<<< orphan*/  LsaSrvReferences ; 
 int /*<<< orphan*/  kuhl_m_sekurlsa_utils_search_generic (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kuhl_m_sekurlsa_utils_search(PKUHL_M_SEKURLSA_CONTEXT cLsass, PKUHL_M_SEKURLSA_LIB pLib)
{
	PVOID *pLogonSessionListCount = (cLsass->osContext.BuildNumber < KULL_M_WIN_BUILD_2K3) ? NULL : ((PVOID *) &LogonSessionListCount);
	return kuhl_m_sekurlsa_utils_search_generic(cLsass, pLib, LsaSrvReferences,  ARRAYSIZE(LsaSrvReferences), (PVOID *) &LogonSessionList, pLogonSessionListCount, NULL, NULL);
}