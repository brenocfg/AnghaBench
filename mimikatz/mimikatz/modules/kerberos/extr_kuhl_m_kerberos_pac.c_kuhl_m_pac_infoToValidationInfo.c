#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  RelativeId; } ;
struct TYPE_5__ {int UserAccountControl; int UserFlags; void* SidCount; scalar_t__ ExtraSids; int /*<<< orphan*/  LogonDomainId; int /*<<< orphan*/  LogonDomainName; TYPE_2__* GroupIds; void* GroupCount; int /*<<< orphan*/  PrimaryGroupId; int /*<<< orphan*/  UserId; int /*<<< orphan*/  EffectiveName; int /*<<< orphan*/  PasswordMustChange; int /*<<< orphan*/  PasswordCanChange; int /*<<< orphan*/  PasswordLastSet; int /*<<< orphan*/  KickOffTime; int /*<<< orphan*/  LogoffTime; int /*<<< orphan*/  LogonTime; } ;
typedef  TYPE_1__* PKERB_VALIDATION_INFO ;
typedef  scalar_t__ PKERB_SID_AND_ATTRIBUTES ;
typedef  int /*<<< orphan*/  PISID ;
typedef  TYPE_2__* PGROUP_MEMBERSHIP ;
typedef  int /*<<< orphan*/ * PFILETIME ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  KERB_VALIDATION_INFO ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  KIWI_NEVERTIME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int USER_DONT_EXPIRE_PASSWORD ; 
 int USER_NORMAL_ACCOUNT ; 

PKERB_VALIDATION_INFO kuhl_m_pac_infoToValidationInfo(PFILETIME authtime, LPCWSTR username, LPCWSTR domainname, LPCWSTR LogonDomainName, PISID sid, ULONG rid, PGROUP_MEMBERSHIP groups, DWORD cbGroups, PKERB_SID_AND_ATTRIBUTES sids, DWORD cbSids)
{
	PKERB_VALIDATION_INFO validationInfo = NULL;
	if(validationInfo = (PKERB_VALIDATION_INFO) LocalAlloc(LPTR, sizeof(KERB_VALIDATION_INFO)))
	{
		validationInfo->LogonTime = *authtime;
		KIWI_NEVERTIME(&validationInfo->LogoffTime);
		KIWI_NEVERTIME(&validationInfo->KickOffTime);
		KIWI_NEVERTIME(&validationInfo->PasswordLastSet);
		KIWI_NEVERTIME(&validationInfo->PasswordCanChange);
		KIWI_NEVERTIME(&validationInfo->PasswordMustChange);
		RtlInitUnicodeString(&validationInfo->EffectiveName, username);
		validationInfo->UserId = rid;
		validationInfo->PrimaryGroupId = groups[0].RelativeId;
		validationInfo->GroupCount = cbGroups;
		validationInfo->GroupIds = groups;
		if(LogonDomainName)
			RtlInitUnicodeString(&validationInfo->LogonDomainName, LogonDomainName);
		validationInfo->LogonDomainId = sid;
		validationInfo->UserAccountControl = USER_DONT_EXPIRE_PASSWORD | USER_NORMAL_ACCOUNT;
		validationInfo->SidCount = cbSids;
		validationInfo->ExtraSids = sids;
		//validationInfo->ResourceGroupDomainSid = NULL;
		//validationInfo->ResourceGroupCount = 0;
		//validationInfo->ResourceGroupIds = NULL;
		if(validationInfo->ExtraSids && validationInfo->SidCount)
			validationInfo->UserFlags |= 0x20;
		//if(validationInfo->ResourceGroupDomainSid && validationInfo->ResourceGroupIds && validationInfo->ResourceGroupCount)
		//	validationInfo->UserFlags |= 0x200;
	}
	return validationInfo;
}