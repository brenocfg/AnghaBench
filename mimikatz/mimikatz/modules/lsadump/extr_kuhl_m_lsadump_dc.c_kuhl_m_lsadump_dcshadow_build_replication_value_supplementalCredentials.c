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
struct TYPE_3__ {int /*<<< orphan*/  valLen; scalar_t__ pVal; } ;
typedef  scalar_t__ PWSTR ;
typedef  scalar_t__ PUSER_PROPERTIES ;
typedef  scalar_t__ PKERB_STORED_CREDENTIAL_NEW ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ATTRVAL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LocalFree (scalar_t__) ; 
 scalar_t__ MIDL_user_allocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlCopyMemory (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials_KerbStoredCredentialNew (scalar_t__,scalar_t__,scalar_t__,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials_UserProperties (scalar_t__*,int /*<<< orphan*/ *,int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials_valueFromArgs (scalar_t__,int,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcsync_descrUserProperties (scalar_t__) ; 

BOOL kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials(ATTRVAL* pVal, PWSTR szValue)
{
	BOOL status = FALSE;
	PWSTR salt;
	PBYTE aes256, aes128;
	PKERB_STORED_CREDENTIAL_NEW kerbCredentials;
	DWORD dwKerbCredentials;
	PUSER_PROPERTIES properties;
	DWORD dwProperties;

	kprintf(L"\n== Encoder helper for supplementalCredentials ==\n\n");
	if(kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials_valueFromArgs(szValue, 4096, &salt, &aes256, &aes128))
	{
		if(kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials_KerbStoredCredentialNew(salt, aes256, aes128, 4096, &kerbCredentials, &dwKerbCredentials))
		{
			if(kuhl_m_lsadump_dcshadow_build_replication_value_supplementalCredentials_UserProperties(&properties, &dwProperties, 1, L"Primary:Kerberos-Newer-Keys", kerbCredentials, dwKerbCredentials))
			{
				kuhl_m_lsadump_dcsync_descrUserProperties(properties);
				if(pVal->pVal = (PBYTE) MIDL_user_allocate(dwProperties))
				{
					pVal->valLen = dwProperties;
					RtlCopyMemory(pVal->pVal, properties, pVal->valLen);
					status = TRUE;
				}
				LocalFree(properties);
			}
			LocalFree(kerbCredentials);
		}
		if(salt)
			LocalFree(salt);
		if(aes256)
			LocalFree(aes256);
		if(aes128)
			LocalFree(aes128);
	}
	return status;
}