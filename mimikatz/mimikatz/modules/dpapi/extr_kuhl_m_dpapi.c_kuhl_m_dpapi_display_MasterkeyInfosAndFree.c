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
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  scalar_t__ LPCGUID ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CALG_SHA1 ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kuhl_m_dpapi_oe_masterkey_add (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ kull_m_crypto_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kull_m_string_displaySID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void kuhl_m_dpapi_display_MasterkeyInfosAndFree(LPCGUID guid, PVOID data, DWORD dataLen, PSID sid)
{
	BYTE digest[SHA_DIGEST_LENGTH];
	
	kprintf(L"  key : ");
	kull_m_string_wprintf_hex(data, dataLen, 0);
	kprintf(L"\n");
	if(kull_m_crypto_hash(CALG_SHA1, data, dataLen, digest, sizeof(digest)))
	{
		kprintf(L"  sha1: ");
		kull_m_string_wprintf_hex(digest, sizeof(digest), 0);
		kprintf(L"\n");
		if(guid)
			kuhl_m_dpapi_oe_masterkey_add(guid, digest, sizeof(digest));
	}
	LocalFree(data);
	if(sid)
	{
		kprintf(L"  sid : ");
		kull_m_string_displaySID(sid);
		kprintf(L"\n");
		LocalFree(sid);
	}
}