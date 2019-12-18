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
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {int dwNameLen; char* pName; scalar_t__ pPrivateKey; scalar_t__ dwPrivateKeyLen; scalar_t__ pPrivateProperties; scalar_t__ dwPrivatePropertiesLen; int /*<<< orphan*/  cbPublicProperties; int /*<<< orphan*/  pPublicProperties; int /*<<< orphan*/  unkArray; int /*<<< orphan*/  dwPublicPropertiesLen; int /*<<< orphan*/  type; int /*<<< orphan*/  unk; int /*<<< orphan*/  dwVersion; } ;
typedef  TYPE_1__* PKULL_M_KEY_CNG_BLOB ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_dpapi_blob_quick_descr (int,scalar_t__) ; 
 int /*<<< orphan*/  kull_m_key_cng_properties_descr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void kull_m_key_cng_descr(DWORD level, PKULL_M_KEY_CNG_BLOB cngKey)
{
	kprintf(L"%*s" L"**KEY (cng)**\n", level << 1, L"");
	if(cngKey)
	{
		kprintf(L"%*s" L"  dwVersion             : %08x - %u\n", level << 1, L"", cngKey->dwVersion, cngKey->dwVersion);
		kprintf(L"%*s" L"  unk                   : %08x - %u\n", level << 1, L"", cngKey->unk, cngKey->unk);
		kprintf(L"%*s" L"  dwNameLen             : %08x - %u\n", level << 1, L"", cngKey->dwNameLen, cngKey->dwNameLen);
		kprintf(L"%*s" L"  type                  : %08x - %u\n", level << 1, L"", cngKey->type, cngKey->type);
		kprintf(L"%*s" L"  dwPublicPropertiesLen : %08x - %u\n", level << 1, L"", cngKey->dwPublicPropertiesLen, cngKey->dwPublicPropertiesLen);
		kprintf(L"%*s" L"  dwPrivatePropertiesLen: %08x - %u\n", level << 1, L"", cngKey->dwPrivatePropertiesLen, cngKey->dwPrivatePropertiesLen);
		kprintf(L"%*s" L"  dwPrivateKeyLen       : %08x - %u\n", level << 1, L"", cngKey->dwPrivateKeyLen, cngKey->dwPrivateKeyLen);
		kprintf(L"%*s" L"  unkArray[16]          : ", level << 1, L""); kull_m_string_wprintf_hex(cngKey->unkArray, sizeof(cngKey->unkArray), 0); kprintf(L"\n");
		kprintf(L"%*s" L"  pName                 : ", level << 1, L""); kprintf(L"%.*s\n", cngKey->dwNameLen / sizeof(wchar_t), cngKey->pName);
		kprintf(L"%*s" L"  pPublicProperties     : ", level << 1, L""); kull_m_key_cng_properties_descr(level + 1, cngKey->pPublicProperties, cngKey->cbPublicProperties);
		kprintf(L"%*s" L"  pPrivateProperties    :\n", level << 1, L"");
		if(cngKey->pPrivateProperties && cngKey->dwPrivatePropertiesLen)
			kull_m_dpapi_blob_quick_descr(level + 1, cngKey->pPrivateProperties); /*kull_m_string_wprintf_hex(cngKey->pPrivateProperties, cngKey->dwPrivatePropertiesLen, 0);*/
		kprintf(L"%*s" L"  pPrivateKey           :\n", level << 1, L"");
		if(cngKey->pPrivateKey && cngKey->dwPrivateKeyLen)
			kull_m_dpapi_blob_quick_descr(level + 1, cngKey->pPrivateKey); /*kull_m_string_wprintf_hex(cngKey->pPrivateKey, cngKey->dwPrivateKeyLen, 0);*/
	}
}