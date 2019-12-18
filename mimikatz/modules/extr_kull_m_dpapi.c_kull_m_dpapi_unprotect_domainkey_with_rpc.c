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
struct TYPE_3__ {int /*<<< orphan*/  dwDomainKeyLen; scalar_t__ dwCredHistLen; scalar_t__ dwBackupKeyLen; scalar_t__ dwMasterKeyLen; } ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  TYPE_1__* PKULL_M_DPAPI_MASTERKEYS ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KULL_M_DPAPI_MASTERKEYS ; 
 int /*<<< orphan*/  LPTR ; 
 int /*<<< orphan*/ * LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 int /*<<< orphan*/  MasterKey ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kull_m_rpc_bkrp_Restore (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ **,scalar_t__*) ; 

BOOL kull_m_dpapi_unprotect_domainkey_with_rpc(PKULL_M_DPAPI_MASTERKEYS masterkeys, PVOID rawMasterkeys, LPCWSTR server, PVOID *output, DWORD *outputLen)
{
	BOOL status = FALSE;
	PBYTE out;
	DWORD dwOut;
	*output = NULL;
	*outputLen = 0;
	if(status = kull_m_rpc_bkrp_Restore(server, (PBYTE) rawMasterkeys + FIELD_OFFSET(KULL_M_DPAPI_MASTERKEYS, MasterKey) + masterkeys->dwMasterKeyLen + masterkeys->dwBackupKeyLen + masterkeys->dwCredHistLen, (DWORD) masterkeys->dwDomainKeyLen, (PVOID *) &out, &dwOut))
	{
		*outputLen = dwOut - sizeof(DWORD);
		if(*output = LocalAlloc(LPTR, *outputLen))
			RtlCopyMemory(*output, out + sizeof(DWORD), dwOut - sizeof(DWORD));
		LocalFree(out);
	}
	return status;
}