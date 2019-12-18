#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ptstrName; } ;
struct TYPE_5__ {int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_7__ {int member_0; TYPE_2__ Trustee; TYPE_1__ member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
typedef  int /*<<< orphan*/  SID_IDENTIFIER_AUTHORITY ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  SC_HANDLE ;
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  TYPE_3__ EXPLICIT_ACCESS ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ AllocateAndInitializeSid (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ BuildSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DACL_SECURITY_INFORMATION ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FreeSid (int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_INHERITANCE ; 
 int /*<<< orphan*/  NO_MULTIPLE_TRUSTEE ; 
 scalar_t__ QueryServiceObjectSecurity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int READ_CONTROL ; 
 int /*<<< orphan*/  SECURITY_WORLD_RID ; 
 int /*<<< orphan*/  SECURITY_WORLD_SID_AUTHORITY ; 
 int SERVICE_ENUMERATE_DEPENDENTS ; 
 int SERVICE_INTERROGATE ; 
 int SERVICE_PAUSE_CONTINUE ; 
 int SERVICE_QUERY_CONFIG ; 
 int SERVICE_QUERY_STATUS ; 
 int SERVICE_START ; 
 int SERVICE_STOP ; 
 int SERVICE_USER_DEFINED_CONTROL ; 
 int /*<<< orphan*/  SET_ACCESS ; 
 int /*<<< orphan*/  SetServiceObjectSecurity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUSTEE_IS_SID ; 
 int /*<<< orphan*/  TRUSTEE_IS_WELL_KNOWN_GROUP ; 

BOOL kull_m_service_addWorldToSD(SC_HANDLE monHandle)
{
	BOOL status = FALSE;
	DWORD dwSizeNeeded;
	PSECURITY_DESCRIPTOR oldSd, newSd;
	SECURITY_DESCRIPTOR dummySdForXP;
	SID_IDENTIFIER_AUTHORITY SIDAuthWorld = SECURITY_WORLD_SID_AUTHORITY;
	EXPLICIT_ACCESS ForEveryOne = {
		SERVICE_QUERY_STATUS | SERVICE_QUERY_CONFIG | SERVICE_INTERROGATE | SERVICE_ENUMERATE_DEPENDENTS | SERVICE_PAUSE_CONTINUE | SERVICE_START | SERVICE_STOP | SERVICE_USER_DEFINED_CONTROL | READ_CONTROL,
		SET_ACCESS,
		NO_INHERITANCE,
		{NULL, NO_MULTIPLE_TRUSTEE, TRUSTEE_IS_SID, TRUSTEE_IS_WELL_KNOWN_GROUP, NULL}
	};
	if(!QueryServiceObjectSecurity(monHandle, DACL_SECURITY_INFORMATION, &dummySdForXP, 0, &dwSizeNeeded) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
	{
		if(oldSd = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, dwSizeNeeded))
		{
			if(QueryServiceObjectSecurity(monHandle, DACL_SECURITY_INFORMATION, oldSd, dwSizeNeeded, &dwSizeNeeded))
			{
				if(AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, (PSID *)&ForEveryOne.Trustee.ptstrName))
				{
					if(BuildSecurityDescriptor(NULL, NULL, 1, &ForEveryOne, 0, NULL, oldSd, &dwSizeNeeded, &newSd) == ERROR_SUCCESS)
					{
						status = SetServiceObjectSecurity(monHandle, DACL_SECURITY_INFORMATION, newSd);
						LocalFree(newSd);
					}
					FreeSid(ForEveryOne.Trustee.ptstrName);
				}
			}
			LocalFree(oldSd);
		}
	}
	return status;
}