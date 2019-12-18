#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  MaximumLength; void* Buffer; } ;
typedef  TYPE_1__ UNICODE_STRING ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
typedef  void* PWSTR ;
typedef  TYPE_1__* PUNICODE_STRING ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_3__ LSA_OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSA_HANDLE ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaFreeMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  LsaOpenPolicy (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsaOpenSecret (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsaQuerySecret (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsaRetrievePrivateData (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__**) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POLICY_GET_PRIVATE_INFORMATION ; 
 int /*<<< orphan*/  RtlCopyMemory (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SECRET_QUERY_VALUE ; 
 int /*<<< orphan*/  STATUS_UNSUCCESSFUL ; 

NTSTATUS kuhl_m_lsadump_LsaRetrievePrivateData(PCWSTR systemName, PCWSTR secretName, PUNICODE_STRING secret, BOOL isSecret)
{
	NTSTATUS status = STATUS_UNSUCCESSFUL;
	LSA_OBJECT_ATTRIBUTES oa = {0};
	LSA_HANDLE hPolicy, hSecret;
	UNICODE_STRING name, system, *cur, *old;
	LARGE_INTEGER curDate, oldDate;

	if(secretName)
	{
		RtlInitUnicodeString(&name, secretName);
		RtlInitUnicodeString(&system, systemName);
		status = LsaOpenPolicy(&system, &oa, POLICY_GET_PRIVATE_INFORMATION, &hPolicy);
		if(NT_SUCCESS(status))
		{
			if(!isSecret)
			{
				status = LsaRetrievePrivateData(hPolicy, &name, &cur);
				if(NT_SUCCESS(status))
				{
					if(cur)
					{
						*secret = *cur;
						if(secret->Buffer = (PWSTR) LocalAlloc(LPTR, secret->MaximumLength))
							RtlCopyMemory(secret->Buffer, cur->Buffer, secret->MaximumLength);
						LsaFreeMemory(cur);
					}
				}
			}
			else
			{
				status = LsaOpenSecret(hPolicy, &name, SECRET_QUERY_VALUE, &hSecret);
				if(NT_SUCCESS(status))
				{
					status = LsaQuerySecret(hSecret, &cur, &curDate, &old, &oldDate);
					if(NT_SUCCESS(status))
					{
						if(cur)
						{
							*secret = *cur;
							if(secret->Buffer = (PWSTR) LocalAlloc(LPTR, secret->MaximumLength))
								RtlCopyMemory(secret->Buffer, cur->Buffer, secret->MaximumLength);
							LsaFreeMemory(cur);
						}
						if(old)
							LsaFreeMemory(old);
					}
					LsaClose(hSecret);
				}
			}
			LsaClose(hPolicy);
		}
	}
	return status;
}