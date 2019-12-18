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
struct TYPE_3__ {scalar_t__ DomainKey; scalar_t__ CredHist; scalar_t__ BackupKey; scalar_t__ MasterKey; scalar_t__ dwDomainKeyLen; scalar_t__ dwCredHistLen; scalar_t__ dwBackupKeyLen; scalar_t__ dwMasterKeyLen; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  szGuid; int /*<<< orphan*/  dwVersion; } ;
typedef  TYPE_1__* PKULL_M_DPAPI_MASTERKEYS ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_dpapi_masterkey_descr (int,scalar_t__) ; 
 int /*<<< orphan*/  kull_m_dpapi_masterkeys_credhist_descr (int,scalar_t__) ; 
 int /*<<< orphan*/  kull_m_dpapi_masterkeys_domainkey_descr (int,scalar_t__) ; 

void kull_m_dpapi_masterkeys_descr(DWORD level, PKULL_M_DPAPI_MASTERKEYS masterkeys)
{
	kprintf(L"%*s" L"**MASTERKEYS**\n", level << 1, L"");
	if(masterkeys)
	{
		kprintf(L"%*s" L"  dwVersion          : %08x - %u\n", level << 1, L"", masterkeys->dwVersion, masterkeys->dwVersion);
		kprintf(L"%*s" L"  szGuid             : {%.36s}\n", level << 1, L"", masterkeys->szGuid);
		kprintf(L"%*s" L"  dwFlags            : %08x - %u\n", level << 1, L"", masterkeys->dwFlags, masterkeys->dwFlags);
		kprintf(L"%*s" L"  dwMasterKeyLen     : %08x - %u\n", level << 1, L"", (DWORD) masterkeys->dwMasterKeyLen, (DWORD) masterkeys->dwMasterKeyLen);
		kprintf(L"%*s" L"  dwBackupKeyLen     : %08x - %u\n", level << 1, L"", (DWORD) masterkeys->dwBackupKeyLen, (DWORD) masterkeys->dwBackupKeyLen);
		kprintf(L"%*s" L"  dwCredHistLen      : %08x - %u\n", level << 1, L"", (DWORD) masterkeys->dwCredHistLen, (DWORD) masterkeys->dwCredHistLen);
		kprintf(L"%*s" L"  dwDomainKeyLen     : %08x - %u\n", level << 1, L"", (DWORD) masterkeys->dwDomainKeyLen, (DWORD) masterkeys->dwDomainKeyLen);
		
		if(masterkeys->MasterKey)
		{
			kprintf(L"%*s" L"[masterkey]\n", level << 1, L"");
			kull_m_dpapi_masterkey_descr(level + 1, masterkeys->MasterKey);
		}
		if(masterkeys->BackupKey)
		{
			kprintf(L"%*s" L"[backupkey]\n", level << 1, L"");
			kull_m_dpapi_masterkey_descr(level + 1, masterkeys->BackupKey);
		}
		if(masterkeys->CredHist)
		{
			kprintf(L"%*s" L"[credhist]\n", level << 1, L"");
			kull_m_dpapi_masterkeys_credhist_descr(level + 1, masterkeys->CredHist);
		}
		if(masterkeys->DomainKey)
		{
			kprintf(L"%*s" L"[domainkey]\n", level << 1, L"");
			kull_m_dpapi_masterkeys_domainkey_descr(level + 1, masterkeys->DomainKey);
		}
		kprintf(L"\n");
	}
}