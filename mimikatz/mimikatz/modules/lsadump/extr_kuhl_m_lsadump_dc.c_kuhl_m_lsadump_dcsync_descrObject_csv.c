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
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PBYTE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  ATTRBLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetSidSubAuthority (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* GetSidSubAuthorityCount (int /*<<< orphan*/ ) ; 
 int LM_NTLM_HASH_LENGTH ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  RtlDecryptDES2blocks1DWORD (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ kull_m_rpc_drsr_findMonoAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_rpc_drsr_findPrintMonoAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kull_m_string_wprintf_hex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOID_ANSI_objectSid ; 
 int /*<<< orphan*/  szOID_ANSI_sAMAccountName ; 
 int /*<<< orphan*/  szOID_ANSI_unicodePwd ; 

void kuhl_m_lsadump_dcsync_descrObject_csv(SCHEMA_PREFIX_TABLE *prefixTable, ATTRBLOCK *attributes)
{
	DWORD rid = 0;
	PBYTE unicodePwd;
	DWORD unicodePwdSize;
	PVOID sid;
	BYTE clearHash[LM_NTLM_HASH_LENGTH];
	if(kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOID_ANSI_sAMAccountName, NULL, NULL) &&
		kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOID_ANSI_objectSid, &sid, NULL) &&
		kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOID_ANSI_unicodePwd, &unicodePwd, &unicodePwdSize))
	{
		rid = *GetSidSubAuthority(sid, *GetSidSubAuthorityCount(sid) - 1);
		kprintf(L"%u\t", rid);
		kull_m_rpc_drsr_findPrintMonoAttr(NULL, prefixTable, attributes, szOID_ANSI_sAMAccountName, FALSE);
		kprintf(L"\t");
		if(NT_SUCCESS(RtlDecryptDES2blocks1DWORD(unicodePwd, &rid, clearHash)))
			kull_m_string_wprintf_hex(clearHash, LM_NTLM_HASH_LENGTH, 0);
		else PRINT_ERROR(L"RtlDecryptDES2blocks1DWORD");
		kprintf(L"\n");
	}
}