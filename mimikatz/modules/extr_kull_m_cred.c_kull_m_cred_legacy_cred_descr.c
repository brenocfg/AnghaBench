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
struct TYPE_3__ {int /*<<< orphan*/  AttributeCount; int /*<<< orphan*/  Attributes; int /*<<< orphan*/  CredentialBlobSize; int /*<<< orphan*/  CredentialBlob; int /*<<< orphan*/  UserName; int /*<<< orphan*/  TargetAlias; int /*<<< orphan*/  Comment; int /*<<< orphan*/  TargetName; int /*<<< orphan*/  unk1; int /*<<< orphan*/  unk0; int /*<<< orphan*/  Persist; int /*<<< orphan*/  unkFlagsOrSize; int /*<<< orphan*/  LastWritten; int /*<<< orphan*/  Type; int /*<<< orphan*/  Flags; int /*<<< orphan*/  credSize; } ;
typedef  TYPE_1__* PKULL_M_CRED_LEGACY_CRED_BLOB ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kull_m_cred_CredPersist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_cred_CredType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_cred_attributes_descr (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_displayFileTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_string_printSuspectUnicodeString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kull_m_cred_legacy_cred_descr(DWORD level, PKULL_M_CRED_LEGACY_CRED_BLOB cred)
{
	kprintf(L"%*s" L"**LEGACY CREDENTIAL**\n", level << 1, L"");
	if(cred)
	{
		kprintf(L"%*s" L"  credSize       : %08x - %u\n\n", level << 1, L"", cred->credSize, cred->credSize);
		kprintf(L"%*s" L"  Flags          : %08x - %u\n", level << 1, L"", cred->Flags, cred->Flags);
		kprintf(L"%*s" L"  Type           : %08x - %u - %s\n", level << 1, L"", cred->Type, cred->Type, kull_m_cred_CredType(cred->Type));
		kprintf(L"%*s" L"  LastWritten    : ", level << 1, L""); kull_m_string_displayFileTime(&cred->LastWritten); kprintf(L"\n");
		kprintf(L"%*s" L"  unkFlagsOrSize : %08x - %u\n", level << 1, L"", cred->unkFlagsOrSize, cred->unkFlagsOrSize);
		kprintf(L"%*s" L"  Persist        : %08x - %u - %s\n", level << 1, L"", cred->Persist, cred->Persist, kull_m_cred_CredPersist(cred->Persist));
		kprintf(L"%*s" L"  AttributeCount : %08x - %u\n", level << 1, L"", cred->AttributeCount, cred->AttributeCount);
		kprintf(L"%*s" L"  unk0           : %08x - %u\n", level << 1, L"", cred->unk0, cred->unk0);
		kprintf(L"%*s" L"  unk1           : %08x - %u\n", level << 1, L"", cred->unk1, cred->unk1);
		kprintf(L"%*s" L"  TargetName     : %s\n", level << 1, L"", cred->TargetName);
		kprintf(L"%*s" L"  Comment        : %s\n", level << 1, L"", cred->Comment);
		kprintf(L"%*s" L"  TargetAlias    : %s\n", level << 1, L"", cred->TargetAlias);
		kprintf(L"%*s" L"  UserName       : %s\n", level << 1, L"", cred->UserName);
		kprintf(L"%*s" L"  CredentialBlob : ", level << 1, L"");
		kull_m_string_printSuspectUnicodeString(cred->CredentialBlob, cred->CredentialBlobSize);
		kprintf(L"\n");
		kprintf(L"%*s" L"  Attributes     : %u\n", level << 1, L"", cred->AttributeCount);
		kull_m_cred_attributes_descr(level + 1, cred->Attributes, cred->AttributeCount);
	}
}