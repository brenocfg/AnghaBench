#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lgrpi1_comment; int /*<<< orphan*/ * lgrpi1_name; int /*<<< orphan*/ * lgrmi3_domainandname; int /*<<< orphan*/  sv100_name; } ;
typedef  TYPE_1__* PSERVER_INFO_100 ;
typedef  TYPE_1__* PLOCALGROUP_MEMBERS_INFO_3 ;
typedef  TYPE_1__* PLOCALGROUP_INFO_1 ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  MAX_PREFERRED_LENGTH ; 
 scalar_t__ NERR_Success ; 
 int /*<<< orphan*/  NetApiBufferFree (TYPE_1__*) ; 
 scalar_t__ NetLocalGroupGetInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ NetLocalGroupGetMembers (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ NetServerGetInfo (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintPaddedMessageString (int,int) ; 
 int /*<<< orphan*/  PrintPadding (int,int) ; 
 int /*<<< orphan*/ ** RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  StdOut ; 
 int wcslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcsncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static
NET_API_STATUS
DisplayLocalGroup(LPWSTR lpGroupName)
{
    PLOCALGROUP_INFO_1 pGroupInfo = NULL;
    PLOCALGROUP_MEMBERS_INFO_3 pMembers = NULL;
    PSERVER_INFO_100 pServer = NULL;
    LPWSTR *pNames = NULL;
    DWORD dwRead = 0;
    DWORD dwTotal = 0;
    DWORD_PTR ResumeHandle = 0;
    DWORD i;
    DWORD len;
    INT nPaddedLength = 18;
    NET_API_STATUS Status;

    Status = NetLocalGroupGetInfo(NULL,
                                  lpGroupName,
                                  1,
                                  (LPBYTE*)&pGroupInfo);
    if (Status != NERR_Success)
        return Status;

    Status = NetLocalGroupGetMembers(NULL,
                                     lpGroupName,
                                     3,
                                     (LPBYTE*)&pMembers,
                                     MAX_PREFERRED_LENGTH,
                                     &dwRead,
                                     &dwTotal,
                                     &ResumeHandle);
    if (Status != NERR_Success)
        goto done;

    Status = NetServerGetInfo(NULL,
                              100,
                              (LPBYTE*)&pServer);
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

    len = wcslen(pServer->sv100_name);
    for (i = 0; i < dwRead; i++)
    {
         if (!wcsncmp(pMembers[i].lgrmi3_domainandname, pServer->sv100_name, len))
             pNames[i] = &pMembers[i].lgrmi3_domainandname[len + 1];
         else
             pNames[i] = pMembers[i].lgrmi3_domainandname;
    }

    PrintPaddedMessageString(4406, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pGroupInfo->lgrpi1_name);

    PrintPaddedMessageString(4407, nPaddedLength);
    ConPrintf(StdOut, L"%s\n", pGroupInfo->lgrpi1_comment);

    ConPuts(StdOut, L"\n");

    PrintMessageString(4408);
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

    if (pServer != NULL)
        NetApiBufferFree(pServer);

    if (pMembers != NULL)
        NetApiBufferFree(pMembers);

    if (pGroupInfo != NULL)
        NetApiBufferFree(pGroupInfo);

    return Status;
}