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
typedef  int /*<<< orphan*/  szDomainNameUnused ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  LookupAccountSidW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SidToUserName(PSID Sid, LPWSTR szBuffer, DWORD BufferSize)
{
    static WCHAR szDomainNameUnused[255];
    DWORD DomainNameLen = sizeof(szDomainNameUnused) / sizeof(szDomainNameUnused[0]);
    SID_NAME_USE Use;

    if (Sid != NULL)
        LookupAccountSidW(NULL, Sid, szBuffer, &BufferSize, szDomainNameUnused, &DomainNameLen, &Use);
}