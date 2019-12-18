#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ offsetToPreviousAuthenticationInformation; scalar_t__ offsetToAuthenticationInformation; scalar_t__ count; } ;
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  TYPE_1__* PNTDS_LSA_AUTH_INFORMATIONS ;
typedef  int /*<<< orphan*/  PNTDS_LSA_AUTH_INFORMATION ;
typedef  int /*<<< orphan*/  PCUNICODE_STRING ;
typedef  scalar_t__ PBYTE ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;
typedef  int /*<<< orphan*/  ATTRBLOCK ;

/* Variables and functions */
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTDS_LSA_AUTH_INFORMATIONS ; 
 int /*<<< orphan*/  count ; 
 int /*<<< orphan*/  kuhl_m_lsadump_trust_authinformation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kull_m_rpc_drsr_findMonoAttr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szOID_ANSI_trustAuthIncoming ; 
 int /*<<< orphan*/  szOID_ANSI_trustAuthOutgoing ; 

void kuhl_m_lsadump_dcsync_descrTrustAuthentication(SCHEMA_PREFIX_TABLE *prefixTable, ATTRBLOCK *attributes, PCUNICODE_STRING domain, PCUNICODE_STRING partner, BOOL isIn)
{
	PBYTE encodedData;
	DWORD encodedDataSize;
	PNTDS_LSA_AUTH_INFORMATIONS authInfos;
	LPCWSTR prefix, prefixOld;
	PCUNICODE_STRING from, dest;

	if(kull_m_rpc_drsr_findMonoAttr(prefixTable, attributes, isIn ? szOID_ANSI_trustAuthIncoming : szOID_ANSI_trustAuthOutgoing, &encodedData, &encodedDataSize))
	{
		if(isIn)
		{
			prefix = L"  In ";
			prefixOld = L" In-1";
			from = domain;
			dest = partner;
		}
		else
		{
			prefix = L" Out ";
			prefixOld = L"Out-1";
			from = partner;
			dest = domain;
		}
		authInfos = (PNTDS_LSA_AUTH_INFORMATIONS) encodedData;
		if(authInfos->count)
		{
			if(authInfos->offsetToAuthenticationInformation)
				kuhl_m_lsadump_trust_authinformation(NULL, 0, (PNTDS_LSA_AUTH_INFORMATION) ((PBYTE) authInfos + FIELD_OFFSET(NTDS_LSA_AUTH_INFORMATIONS, count) + authInfos->offsetToAuthenticationInformation), prefix, from, dest);
			if(authInfos->offsetToPreviousAuthenticationInformation)
				kuhl_m_lsadump_trust_authinformation(NULL, 0, (PNTDS_LSA_AUTH_INFORMATION) ((PBYTE) authInfos + FIELD_OFFSET(NTDS_LSA_AUTH_INFORMATIONS, count) + authInfos->offsetToPreviousAuthenticationInformation), prefixOld, from, dest);
		}
	}
}