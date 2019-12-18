#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  passwordHash ;
typedef  int /*<<< orphan*/  derivedkey ;
struct TYPE_16__ {int /*<<< orphan*/  guid; } ;
struct TYPE_19__ {int /*<<< orphan*/ * pSid; TYPE_3__ header; } ;
struct TYPE_15__ {int flags; int /*<<< orphan*/ * sha1hashDerived; } ;
struct TYPE_18__ {TYPE_2__ data; } ;
struct TYPE_14__ {int /*<<< orphan*/  guid; } ;
struct TYPE_17__ {int __dwCount; TYPE_6__** entries; TYPE_1__ current; } ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  TYPE_4__* PKULL_M_DPAPI_CREDHIST ;
typedef  TYPE_5__* PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY ;
typedef  int /*<<< orphan*/ * PBYTE ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/ * LPCGUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_SHA1 ; 
 scalar_t__ ConvertSidToStringSid (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ ConvertStringSidToSid (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ FALSE ; 
 int KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_SHA1 ; 
 int LM_NTLM_HASH_LENGTH ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_display_CredHist (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_credential_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_credential_copyEntryWithNewGuid (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_credential_descr (TYPE_5__*) ; 
 TYPE_5__* kuhl_m_dpapi_oe_credential_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_crypto_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kull_m_crypto_hmac (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* kull_m_dpapi_credhist_create (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kull_m_dpapi_credhist_delete (TYPE_4__*) ; 
 int /*<<< orphan*/  kull_m_dpapi_credhist_descr (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ kull_m_dpapi_unprotect_credhist_entry_with_shaDerivedkey (TYPE_6__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_file_readData (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_stringToHex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ wcslen (int /*<<< orphan*/ *) ; 

NTSTATUS kuhl_m_dpapi_credhist(int argc, wchar_t * argv[])
{
	PBYTE buffer;
	DWORD szBuffer, i;
	LPCWSTR szIn = NULL, szSid = NULL, szHash = NULL, szPassword = NULL;
	PWSTR convertedSid = NULL;
	PSID pSid = NULL, prevSid = NULL;
	LPCGUID prevGuid;
	PKULL_M_DPAPI_CREDHIST credhist;
	PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY pCredentialEntry = NULL;
	BYTE passwordHash[SHA_DIGEST_LENGTH], derivedkey[SHA_DIGEST_LENGTH], sha1[SHA_DIGEST_LENGTH], ntlm[LM_NTLM_HASH_LENGTH];
	BOOL hashOk = FALSE;

	if(kull_m_string_args_byName(argc, argv, L"in", &szIn, NULL))
	{
		if(kull_m_file_readData(szIn, &buffer, &szBuffer))
		{
			if(credhist = kull_m_dpapi_credhist_create(buffer, szBuffer))
			{
				kull_m_dpapi_credhist_descr(0, credhist);

				if(kull_m_string_args_byName(argc, argv, L"sid", &szSid, NULL))
				{
					if(ConvertStringSidToSid(szSid, &pSid))
						prevSid = pSid;
					else PRINT_ERROR_AUTO(L"ConvertStringSidToSid");
				}
				
				if(kull_m_string_args_byName(argc, argv, L"password", &szPassword, NULL))
					hashOk = kull_m_crypto_hash(CALG_SHA1, szPassword, (DWORD) wcslen(szPassword) * sizeof(wchar_t), passwordHash, sizeof(passwordHash));
				else if(kull_m_string_args_byName(argc, argv, L"sha1", &szHash, NULL))
					hashOk = kull_m_string_stringToHex(szHash, passwordHash, sizeof(passwordHash));

				prevGuid = &credhist->current.guid;
				if(!prevSid && credhist->__dwCount)
					prevSid = credhist->entries[0]->pSid;

				for(i = 0; prevSid && (i < credhist->__dwCount); i++)
				{
					if(ConvertSidToStringSid(prevSid, &convertedSid))
					{
						pCredentialEntry = kuhl_m_dpapi_oe_credential_get(NULL, prevGuid);
						if(!pCredentialEntry)
							pCredentialEntry = kuhl_m_dpapi_oe_credential_get(convertedSid, NULL);
						if(pCredentialEntry && (pCredentialEntry->data.flags & KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_SHA1))
						{
							kprintf(L"\n  [entry %u] with volatile cache: ", i); kuhl_m_dpapi_oe_credential_descr(pCredentialEntry);
							if(kull_m_dpapi_unprotect_credhist_entry_with_shaDerivedkey(credhist->entries[i], pCredentialEntry->data.sha1hashDerived, sizeof(pCredentialEntry->data.sha1hashDerived), ntlm, sha1))
							{
								kuhl_m_dpapi_oe_credential_copyEntryWithNewGuid(pCredentialEntry, prevGuid);
								kuhl_m_dpapi_display_CredHist(credhist->entries[i], ntlm, sha1);
							}
						}
						else if(hashOk)
						{
							kprintf(L"\n  [entry %u] with SHA1 and SID: ", i); kull_m_string_wprintf_hex(passwordHash, sizeof(passwordHash), 0); kprintf(L"\n");
							if(kull_m_crypto_hmac(CALG_SHA1, passwordHash, sizeof(passwordHash), convertedSid, (DWORD) (wcslen(convertedSid) + 1) * sizeof(wchar_t), derivedkey, sizeof(derivedkey)))
								if(kull_m_dpapi_unprotect_credhist_entry_with_shaDerivedkey(credhist->entries[i], derivedkey, sizeof(derivedkey), ntlm, sha1))
								{
									kuhl_m_dpapi_oe_credential_add(convertedSid, prevGuid, NULL, passwordHash, NULL, szPassword);
									kuhl_m_dpapi_display_CredHist(credhist->entries[i], ntlm, sha1);
								}
						}
						LocalFree(convertedSid);
					}
					prevGuid = &credhist->entries[i]->header.guid;
					prevSid = credhist->entries[i]->pSid;
				}

				if(pSid)
					LocalFree(pSid);
				
				kull_m_dpapi_credhist_delete(credhist);
			}
			LocalFree(buffer);
		}
	}
	else PRINT_ERROR(L"Input credhist file needed (/in:file)\n");
	return STATUS_SUCCESS;
}