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
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ATTRBLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcsync_descrSecret (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcsync_descrTrust (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcsync_descrUser (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_rpc_drsr_findMonoAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_rpc_drsr_findPrintMonoAttr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szOID_ANSI_currentValue ; 
 int /*<<< orphan*/  szOID_ANSI_name ; 
 int /*<<< orphan*/  szOID_ANSI_sAMAccountName ; 
 int /*<<< orphan*/  szOID_ANSI_trustPartner ; 

void kuhl_m_lsadump_dcsync_descrObject(SCHEMA_PREFIX_TABLE *prefixTable, ATTRBLOCK *attributes, LPCWSTR szSrcDomain, BOOL someExport)
{
	kull_m_rpc_drsr_findPrintMonoAttr(L"\nObject RDN           : ", prefixTable, attributes, szOID_ANSI_name, TRUE);
	kprintf(L"\n");
	if(kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOID_ANSI_sAMAccountName, NULL, NULL))
		kuhl_m_lsadump_dcsync_descrUser(prefixTable, attributes);
	else if(kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOID_ANSI_trustPartner, NULL, NULL))
		kuhl_m_lsadump_dcsync_descrTrust(prefixTable, attributes, szSrcDomain);
	else if(kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, szOID_ANSI_currentValue, NULL, NULL))
		kuhl_m_lsadump_dcsync_descrSecret(prefixTable, attributes, someExport);
}