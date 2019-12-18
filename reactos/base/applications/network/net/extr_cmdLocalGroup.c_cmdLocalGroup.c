#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  int ULONG ;
struct TYPE_10__ {int* lgrpi0_name; } ;
struct TYPE_9__ {int* lgrpi1_name; int* lgrpi1_comment; } ;
struct TYPE_8__ {int* lgrpi1002_comment; } ;
struct TYPE_7__ {int* lgrmi3_domainandname; } ;
typedef  int* NET_API_STATUS ;
typedef  int* LPWSTR ;
typedef  TYPE_1__* LPLOCALGROUP_MEMBERS_INFO_3 ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  TYPE_2__ LOCALGROUP_INFO_1002 ;
typedef  TYPE_3__ LOCALGROUP_INFO_1 ;
typedef  TYPE_4__ LOCALGROUP_INFO_0 ;
typedef  int INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int* DisplayLocalGroup (int*) ; 
 int* EnumerateLocalGroups () ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  MSG_LOCALGROUP_HELP ; 
 int /*<<< orphan*/  MSG_LOCALGROUP_SYNTAX ; 
 int* NetLocalGroupAdd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int* NetLocalGroupAddMembers (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int) ; 
 int* NetLocalGroupDel (int /*<<< orphan*/ *,int*) ; 
 int* NetLocalGroupDelMembers (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int) ; 
 int* NetLocalGroupSetInfo (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintErrorMessage (int) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 TYPE_1__* RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ TRUE ; 
 scalar_t__ _wcsicmp (int*,char*) ; 
 scalar_t__ _wcsnicmp (int*,char*,int) ; 

INT
cmdLocalGroup(
    INT argc,
    WCHAR **argv)
{
    INT i, j;
    INT result = 0;
    ULONG dwMemberCount = 0;
    BOOL bAdd = FALSE;
    BOOL bDelete = FALSE;
#if 0
    BOOL bDomain = FALSE;
#endif
    LPWSTR lpGroupName = NULL;
    LPWSTR lpComment = NULL;
    LPLOCALGROUP_MEMBERS_INFO_3 lpMembers = NULL;
    LOCALGROUP_INFO_0 Info0;
    LOCALGROUP_INFO_1 Info1;
    LOCALGROUP_INFO_1002 Info1002;
    NET_API_STATUS Status;

    if (argc == 2)
    {
        Status = EnumerateLocalGroups();
        ConPrintf(StdOut, L"Status: %lu\n", Status);
        return 0;
    }
    else if (argc == 3)
    {
        Status = DisplayLocalGroup(argv[2]);
        ConPrintf(StdOut, L"Status: %lu\n", Status);
        return 0;
    }

    i = 2;
    if (argv[i][0] != L'/')
    {
        lpGroupName = argv[i];
        i++;
    }

    for (j = i; j < argc; j++)
    {
        if (argv[j][0] == L'/')
            break;

        dwMemberCount++;
    }

    ConPrintf(StdOut, L"Member count: %lu\n", dwMemberCount);

    if (dwMemberCount > 0)
    {
        lpMembers = RtlAllocateHeap(RtlGetProcessHeap(),
                                    HEAP_ZERO_MEMORY,
                                    dwMemberCount * sizeof(LPLOCALGROUP_MEMBERS_INFO_3));
        if (lpMembers == NULL)
            return 0;
    }

    j = 0;
    for (; i < argc; i++)
    {
        if (argv[i][0] == L'/')
            break;

        lpMembers[j].lgrmi3_domainandname = argv[i];
        j++;
    }

    for (; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_LOCALGROUP_SYNTAX);
            PrintNetMessage(MSG_LOCALGROUP_HELP);
            return 0;
        }
        else if (_wcsicmp(argv[i], L"/add") == 0)
        {
            bAdd = TRUE;
        }
        else if (_wcsicmp(argv[i], L"/delete") == 0)
        {
            bDelete = TRUE;
        }
        else if (_wcsnicmp(argv[i], L"/comment:", 9) == 0)
        {
            lpComment = &argv[i][9];
        }
        else if (_wcsicmp(argv[i], L"/domain") == 0)
        {
            ConPuts(StdErr, L"The /DOMAIN option is not supported yet.\n");
#if 0
            bDomain = TRUE;
#endif
        }
        else
        {
            PrintErrorMessage(3506/*, argv[i]*/);
            result = 1;
            goto done;
        }
    }

    if (lpGroupName == NULL)
    {
        result = 1;
        goto done;
    }

    if (bAdd && bDelete)
    {
        result = 1;
        goto done;
    }

#if 0
    ConPrintf(StdOut, L"Group:\n  %s\n", lpGroupName);

    if (lpMembers != NULL)
    {
        ConPuts(StdOut, L"\nMembers:\n");
        for (i = 0; i < dwMemberCount; i++)
            ConPrintf(StdOut, L"  %s\n", lpMembers[i].lgrmi3_domainandname);
    }

    if (lpComment != NULL)
    {
        ConPrintf(StdOut, L"\nComment:\n  %s\n", lpComment);
    }
#endif

    if (lpMembers == NULL)
    {
        if (!bAdd && !bDelete && lpComment != NULL)
        {
            /* Set group comment */
            Info1002.lgrpi1002_comment = lpComment;
            Status = NetLocalGroupSetInfo(NULL,
                                          lpGroupName,
                                          1002,
                                          (LPBYTE)&Info1002,
                                          NULL);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else if (bAdd && !bDelete)
        {
            /* Add the group */
            if (lpComment == NULL)
            {
                Info0.lgrpi0_name = lpGroupName;
            }
            else
            {
                Info1.lgrpi1_name = lpGroupName;
                Info1.lgrpi1_comment = lpComment;
            }

            Status = NetLocalGroupAdd(NULL,
                                      (lpComment == NULL) ? 0 : 1,
                                      (lpComment == NULL) ? (LPBYTE)&Info0 : (LPBYTE)&Info1,
                                      NULL);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else if (!bAdd && bDelete && lpComment == NULL)
        {
            /* Delete the group */
            Status = NetLocalGroupDel(NULL,
                                      lpGroupName);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else
        {
            result = 1;
        }
    }
    else
    {
        if (bAdd && !bDelete && lpComment == NULL)
        {
            /* Add group members */
            Status = NetLocalGroupAddMembers(NULL,
                                             lpGroupName,
                                             3,
                                             (LPBYTE)lpMembers,
                                             dwMemberCount);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else if (!bAdd && bDelete && lpComment == NULL)
        {
            /* Delete group members */
            Status = NetLocalGroupDelMembers(NULL,
                                             lpGroupName,
                                             3,
                                             (LPBYTE)lpMembers,
                                             dwMemberCount);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else
        {
            result = 1;
        }
    }

done:
    if (lpMembers != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, lpMembers);

    if (result != 0)
    {
        PrintMessageString(4381);
        ConPuts(StdOut, L"\n");
        PrintNetMessage(MSG_LOCALGROUP_SYNTAX);
    }

    return result;
}