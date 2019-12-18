#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_8__ {scalar_t__ Buffer; scalar_t__ MaximumLength; scalar_t__ Length; } ;
typedef  TYPE_1__ UNICODE_STRING ;
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  scalar_t__ PWSTR ;
typedef  scalar_t__ PBYTE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  ATTRBLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlFreeUnicodeString (TYPE_1__*) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlUpcaseUnicodeString (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcsync_descrTrustAuthentication (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_rpc_drsr_findMonoAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  szOID_ANSI_trustPartner ; 

void kuhl_m_lsadump_dcsync_descrTrust(SCHEMA_PREFIX_TABLE *prefixTable, ATTRBLOCK *attributes, LPCWSTR szSrcDomain)
{
	PBYTE encodedData;
	DWORD encodedDataSize;
	UNICODE_STRING uPartner, uDomain, uUpcasePartner, uUpcaseDomain;
	
	kprintf(L"** TRUSTED DOMAIN - Antisocial **\n\n");
	
	if(kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOID_ANSI_trustPartner, &encodedData, &encodedDataSize))
	{
		uPartner.Length = uPartner.MaximumLength = (USHORT) encodedDataSize;
		uPartner.Buffer = (PWSTR) encodedData;
		kprintf(L"Partner              : %wZ\n", &uPartner);
		if(NT_SUCCESS(RtlUpcaseUnicodeString(&uUpcasePartner, &uPartner, TRUE)))
		{
			RtlInitUnicodeString(&uDomain, szSrcDomain);
			if(NT_SUCCESS(RtlUpcaseUnicodeString(&uUpcaseDomain, &uDomain, TRUE)))
			{
				kuhl_m_lsadump_dcsync_descrTrustAuthentication(prefixTable, attributes, &uUpcaseDomain, &uUpcasePartner, TRUE);
				kuhl_m_lsadump_dcsync_descrTrustAuthentication(prefixTable, attributes, &uUpcaseDomain, &uUpcasePartner, FALSE);
				RtlFreeUnicodeString(&uUpcaseDomain);
			}
			RtlFreeUnicodeString(&uUpcasePartner);
		}
	}
}