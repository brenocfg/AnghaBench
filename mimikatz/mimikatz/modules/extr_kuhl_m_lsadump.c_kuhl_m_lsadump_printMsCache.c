#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* Buffer; int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; } ;
struct TYPE_7__ {int /*<<< orphan*/  MaximumLength; int /*<<< orphan*/  Length; void* Buffer; } ;
struct TYPE_11__ {TYPE_2__ UserName; TYPE_1__ Domain; } ;
struct TYPE_10__ {int /*<<< orphan*/  mshashdata; } ;
struct TYPE_9__ {scalar_t__ enc_data; int /*<<< orphan*/  szDomainName; int /*<<< orphan*/  szUserName; } ;
typedef  void* PWSTR ;
typedef  TYPE_3__* PMSCACHE_ENTRY ;
typedef  TYPE_4__* PMSCACHE_DATA ;
typedef  scalar_t__ PBYTE ;
typedef  TYPE_5__ MSCACHE_ENTRY_PTR ;
typedef  int /*<<< orphan*/  MSCACHE_DATA ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  LM_NTLM_HASH_LENGTH ; 
 scalar_t__ SIZE_ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kuhl_m_lsadump_printMsCache(PMSCACHE_ENTRY entry, CHAR version)
{
	//DWORD i;
	MSCACHE_ENTRY_PTR ptr;
	ptr.UserName.Buffer = (PWSTR) ((PBYTE) entry->enc_data + sizeof(MSCACHE_DATA));
	ptr.UserName.Length = ptr.UserName.MaximumLength = entry->szUserName;
	ptr.Domain.Buffer = (PWSTR) ((PBYTE) ptr.UserName.Buffer + SIZE_ALIGN(entry->szUserName, 4));
	ptr.Domain.Length = ptr.Domain.MaximumLength = entry->szDomainName;
	//ptr.DnsDomainName.Buffer = (PWSTR) ((PBYTE) ptr.Domain.Buffer + SIZE_ALIGN(entry->szDomainName, 4));
	//ptr.DnsDomainName.Length = ptr.DnsDomainName.MaximumLength = entry->szDnsDomainName;
	//ptr.Upn.Buffer = (PWSTR) ((PBYTE) ptr.DnsDomainName.Buffer + SIZE_ALIGN(entry->szDnsDomainName, 4));
	//ptr.Upn.Length = ptr.Upn.MaximumLength = entry->szupn;
	//ptr.EffectiveName.Buffer = (PWSTR) ((PBYTE) ptr.Upn.Buffer + SIZE_ALIGN(entry->szupn, 4));
	//ptr.EffectiveName.Length = ptr.EffectiveName.MaximumLength = entry->szEffectiveName;
	//ptr.FullName.Buffer = (PWSTR) ((PBYTE) ptr.EffectiveName.Buffer + SIZE_ALIGN(entry->szEffectiveName, 4));
	//ptr.FullName.Length = ptr.FullName.MaximumLength = entry->szFullName;
	//ptr.LogonScript.Buffer = (PWSTR) ((PBYTE) ptr.FullName.Buffer + SIZE_ALIGN(entry->szFullName, 4));
	//ptr.LogonScript.Length = ptr.LogonScript.MaximumLength = entry->szlogonScript;
	//ptr.ProfilePath.Buffer = (PWSTR) ((PBYTE) ptr.LogonScript.Buffer + SIZE_ALIGN(entry->szlogonScript, 4));
	//ptr.ProfilePath.Length = ptr.ProfilePath.MaximumLength = entry->szprofilePath;
	//ptr.HomeDirectory.Buffer = (PWSTR) ((PBYTE) ptr.ProfilePath.Buffer + SIZE_ALIGN(entry->szprofilePath, 4));
	//ptr.HomeDirectory.Length = ptr.HomeDirectory.MaximumLength = entry->szhomeDirectory;
	//ptr.HomeDirectoryDrive.Buffer = (PWSTR) ((PBYTE) ptr.HomeDirectory.Buffer + SIZE_ALIGN(entry->szhomeDirectory, 4));
	//ptr.HomeDirectoryDrive.Length = ptr.HomeDirectoryDrive.MaximumLength = entry->szhomeDirectoryDrive;
	//ptr.Groups = (PGROUP_MEMBERSHIP) ((PBYTE) ptr.HomeDirectoryDrive.Buffer + SIZE_ALIGN(entry->szhomeDirectoryDrive, 4));
	//ptr.LogonDomainName.Buffer = (PWSTR) ((PBYTE) ptr.Groups + SIZE_ALIGN(entry->groupCount * sizeof(GROUP_MEMBERSHIP), 4));
	//ptr.LogonDomainName.Length = ptr.LogonDomainName.MaximumLength = entry->szlogonDomainName;

	//kprintf(L"UserName     : %wZ\n", &ptr.UserName);
	//kprintf(L"Domain       : %wZ\n", &ptr.Domain);
	//kprintf(L"DnsDomainName: %wZ\n", &ptr.DnsDomainName);
	//kprintf(L"Upn          : %wZ\n", &ptr.Upn);
	//kprintf(L"EffectiveName: %wZ\n", &ptr.EffectiveName);
	//kprintf(L"FullName     : %wZ\n", &ptr.FullName);
	//kprintf(L"LogonScript  : %wZ\n", &ptr.LogonScript);
	//kprintf(L"ProfilePath  : %wZ\n", &ptr.ProfilePath);
	//kprintf(L"HomeDirectory: %wZ\n", &ptr.HomeDirectory);
	//kprintf(L"HomeDirectoryDrive: %wZ\n", &ptr.HomeDirectoryDrive);
	//kprintf(L"Groups       :");
	//for(i = 0; i < entry->groupCount; i++)
	//	kprintf(L" %u", ptr.Groups[i].RelativeId);
	//kprintf(L"\n");
	//kprintf(L"LogonDomainName: %wZ\n", &ptr.LogonDomainName);
	//kprintf(L"sidCount: %u\n", entry->sidCount);
	kprintf(L"User      : %wZ\\%wZ\n", &ptr.Domain, &ptr.UserName);
	kprintf(L"MsCacheV%c : ", version); kull_m_string_wprintf_hex(((PMSCACHE_DATA) entry->enc_data)->mshashdata, LM_NTLM_HASH_LENGTH, 0); kprintf(L"\n");
}