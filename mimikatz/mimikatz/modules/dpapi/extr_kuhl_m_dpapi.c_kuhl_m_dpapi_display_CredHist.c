#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  guid; } ;
struct TYPE_5__ {TYPE_1__ header; int /*<<< orphan*/  pSid; } ;
typedef  int /*<<< orphan*/  PWSTR ;
typedef  TYPE_2__* PKULL_M_DPAPI_CREDHIST_ENTRY ;
typedef  int /*<<< orphan*/  LPCVOID ;

/* Variables and functions */
 scalar_t__ ConvertSidToStringSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LM_NTLM_HASH_LENGTH ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_credential_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_displayGUID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_displaySID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kuhl_m_dpapi_display_CredHist(PKULL_M_DPAPI_CREDHIST_ENTRY entry, LPCVOID ntlm, LPCVOID sha1)
{
	PWSTR currentStringSid;
	kprintf(L"   "); kull_m_string_displaySID(entry->pSid); kprintf(L" -- "); kull_m_string_displayGUID(&entry->header.guid); kprintf(L"\n");
	kprintf(L"   > NTLM: "); kull_m_string_wprintf_hex(ntlm, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
	kprintf(L"   > SHA1: "); kull_m_string_wprintf_hex(sha1, SHA_DIGEST_LENGTH, 0); kprintf(L"\n");
	if(ConvertSidToStringSid(entry->pSid, &currentStringSid))
	{
		kuhl_m_dpapi_oe_credential_add(currentStringSid, &entry->header.guid, ntlm, sha1, NULL, NULL);
		LocalFree(currentStringSid);
	}
}