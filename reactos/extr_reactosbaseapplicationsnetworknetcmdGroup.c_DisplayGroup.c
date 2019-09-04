#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ grpi1_comment; scalar_t__ grpi1_name; scalar_t__ grui0_name; } ;
typedef  TYPE_1__* PGROUP_USERS_INFO_0 ;
typedef  TYPE_1__* PGROUP_INFO_1 ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  scalar_t__ LPWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetGroupGetInfo (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NetGroupGetUsers (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintPaddedMessageString (int,int) ; 
 int /*<<< orphan*/  PrintPadding (int,int) ; 
 scalar_t__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  StdOut ; 

__attribute__((used)) static
NET_API_STATUS
DisplayGroup(LPWSTR lpGroupName)
{
    PGROUP_INFO_1 pGroupInfo = NULL;
    PGROUP_USERS_INFO_0 pUsers = NULL;
    LPWSTR *pNames = NULL;
    DWORD dwRead = 0;
    DWORD dwTotal = 0;
    DWORD_PTR ResumeHandle = 0;
    DWORD i;
    INT nPaddedLength = 15;
    NET_API_STATUS Status;

    Status = NetGroupGetInfo(NULL,
                             lpGroupName,
                             1,
                             (LPBYTE*)&pGroupInfo);
    if (Status != NERR_Success)
        return Status;

    Status = NetGroupGetUsers(NULL,
                              lpGroupName,
                              0,
                              (LPBYTE*)&pUsers,
                              MAX_PREFERRED_LENGTH,
                              &dwRead,
                              &dwTotal,
                              &ResumeHandle);
    if (Status != NERR_Success)
        goto done;

    pNames = RtlAllocateHeap(RtlGetProcessHeap(),
                             HEAP_ZERO_MEMORY,
                             dwRead * sizeof(LPWSTR));
    if (pNames == NULL)
    {
        Status = ERROR_OUTOFMEMORY;
        goto done;
    }

    for (i = 0; i < dwRead; i++)
    {
        pNames[i] = pUsers[i].grui0_name;
    }

    PrintPaddedMessageString(4401, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pGroupInfo->grpi1_name);

    PrintPaddedMessageString(4402, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pGroupInfo->grpi1_comment);

    ConPuts(StdOut, L"\n");

    PrintMessageString(4403);
    ConPuts(StdOut, L"\n");

    PrintPadding(L'-', 79);
    ConPuts(StdOut, L"\n");

    for (i = 0; i < dwRead; i++)
    {
        if (pNames[i])
            ConPrintf(StdOut, L"%s\n", pNames[i]);
    }

done:
    if (pNames != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, pNames);

    if (pUsers != NULL)
        NetApiBufferFree(pUsers);

    if (pGroupInfo != NULL)
        NetApiBufferFree(pGroupInfo);

    return Status;
}