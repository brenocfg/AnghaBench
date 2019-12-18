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
typedef  int /*<<< orphan*/  RPC_BINDING_HANDLE ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DS_WRITABLE_REQUIRED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int MIMIKATZ_NT_MAJOR_VERSION ; 
 int /*<<< orphan*/  RPC_C_AUTHN_GSS_KERBEROS ; 
 int /*<<< orphan*/  RPC_C_AUTHN_GSS_NEGOTIATE ; 
 int /*<<< orphan*/  RPC_C_IMP_LEVEL_IMPERSONATE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ kull_m_net_getDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kull_m_rpc_createBinding (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOL kull_m_rpc_bkrp_createBinding(LPCWSTR NetworkAddr, RPC_BINDING_HANDLE *hBinding)
{
	BOOL status = FALSE;
	LPWSTR szTmpDc = NULL;
	if(!NetworkAddr)
		if(kull_m_net_getDC(NULL, DS_WRITABLE_REQUIRED, &szTmpDc))
			NetworkAddr = szTmpDc;
	if(NetworkAddr)
		status = kull_m_rpc_createBinding(NULL, L"ncacn_np", NetworkAddr, L"\\pipe\\protected_storage", L"ProtectedStorage", TRUE, (MIMIKATZ_NT_MAJOR_VERSION < 6) ? RPC_C_AUTHN_GSS_KERBEROS : RPC_C_AUTHN_GSS_NEGOTIATE, NULL, RPC_C_IMP_LEVEL_IMPERSONATE, hBinding, NULL);
	if(szTmpDc)
		LocalFree(szTmpDc);
	return status;
}