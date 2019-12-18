#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
typedef  int ULONG ;
struct TYPE_6__ {int* grpi0_name; } ;
struct TYPE_5__ {int* grpi1_name; int* grpi1_comment; } ;
struct TYPE_4__ {int* grpi1002_comment; } ;
typedef  int* PWSTR ;
typedef  int /*<<< orphan*/  PGROUP_USERS_INFO_0 ;
typedef  scalar_t__ NET_API_STATUS ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int INT ;
typedef  TYPE_1__ GROUP_INFO_1002 ;
typedef  TYPE_2__ GROUP_INFO_1 ;
typedef  TYPE_3__ GROUP_INFO_0 ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ DisplayGroup (int*) ; 
 scalar_t__ EnumerateGroups () ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  MSG_GROUP_HELP ; 
 int /*<<< orphan*/  MSG_GROUP_SYNTAX ; 
 scalar_t__ NERR_Success ; 
 scalar_t__ NetGroupAdd (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ NetGroupAddUser (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ NetGroupDel (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ NetGroupDelUser (int /*<<< orphan*/ *,int*,int*) ; 
 scalar_t__ NetGroupSetInfo (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintErrorMessage (int) ; 
 int /*<<< orphan*/  PrintMessageString (int) ; 
 int /*<<< orphan*/  PrintNetMessage (int /*<<< orphan*/ ) ; 
 int** RtlAllocateHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ TRUE ; 
 scalar_t__ _wcsicmp (int*,char*) ; 
 scalar_t__ _wcsnicmp (int*,char*,int) ; 

INT
cmdGroup(
    INT argc,
    WCHAR **argv)
{
    INT i, j;
    INT result = 0;
    ULONG dwUserCount = 0;
    BOOL bAdd = FALSE;
    BOOL bDelete = FALSE;
#if 0
    BOOL bDomain = FALSE;
#endif
    PWSTR pGroupName = NULL;
    PWSTR pComment = NULL;
    PWSTR *pUsers = NULL;
    GROUP_INFO_0 Info0;
    GROUP_INFO_1 Info1;
    GROUP_INFO_1002 Info1002;
    NET_API_STATUS Status;

    if (argc == 2)
    {
        Status = EnumerateGroups();
        ConPrintf(StdOut, L"Status: %lu\n", Status);
        return 0;
    }
    else if (argc == 3)
    {
        Status = DisplayGroup(argv[2]);
        ConPrintf(StdOut, L"Status: %lu\n", Status);
        return 0;
    }

    i = 2;
    if (argv[i][0] != L'/')
    {
        pGroupName = argv[i];
        i++;
    }

    for (j = i; j < argc; j++)
    {
        if (argv[j][0] == L'/')
            break;

        dwUserCount++;
    }

    if (dwUserCount > 0)
    {
        pUsers = RtlAllocateHeap(RtlGetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 dwUserCount * sizeof(PGROUP_USERS_INFO_0));
        if (pUsers == NULL)
            return 0;
    }

    j = 0;
    for (; i < argc; i++)
    {
        if (argv[i][0] == L'/')
            break;

        pUsers[j] = argv[i];
        j++;
    }

    for (; i < argc; i++)
    {
        if (_wcsicmp(argv[i], L"/help") == 0)
        {
            PrintMessageString(4381);
            ConPuts(StdOut, L"\n");
            PrintNetMessage(MSG_GROUP_SYNTAX);
            PrintNetMessage(MSG_GROUP_HELP);
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
            pComment = &argv[i][9];
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

    if (pGroupName == NULL)
    {
        result = 1;
        goto done;
    }

    if (bAdd && bDelete)
    {
        result = 1;
        goto done;
    }

    if (pUsers == NULL)
    {
        if (!bAdd && !bDelete && pComment != NULL)
        {
            /* Set group comment */
            Info1002.grpi1002_comment = pComment;
            Status = NetGroupSetInfo(NULL,
                                     pGroupName,
                                     1002,
                                     (LPBYTE)&Info1002,
                                     NULL);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else if (bAdd && !bDelete)
        {
            /* Add the group */
            if (pComment == NULL)
            {
                Info0.grpi0_name = pGroupName;
            }
            else
            {
                Info1.grpi1_name = pGroupName;
                Info1.grpi1_comment = pComment;
            }

            Status = NetGroupAdd(NULL,
                                 (pComment == NULL) ? 0 : 1,
                                 (pComment == NULL) ? (LPBYTE)&Info0 : (LPBYTE)&Info1,
                                 NULL);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else if (!bAdd && bDelete && pComment == NULL)
        {
            /* Delete the group */
            Status = NetGroupDel(NULL,
                                 pGroupName);
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else
        {
            result = 1;
        }
    }
    else
    {
        if (bAdd && !bDelete && pComment == NULL)
        {
            /* Add group user */
            for (i = 0; i < dwUserCount; i++)
            {
                Status = NetGroupAddUser(NULL,
                                         pGroupName,
                                         pUsers[i]);
                if (Status != NERR_Success)
                    break;
            }
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else if (!bAdd && bDelete && pComment == NULL)
        {
            /* Delete group members */
            for (i = 0; i < dwUserCount; i++)
            {
                Status = NetGroupDelUser(NULL,
                                         pGroupName,
                                         pUsers[i]);
                if (Status != NERR_Success)
                    break;
            }
            ConPrintf(StdOut, L"Status: %lu\n", Status);
        }
        else
        {
            result = 1;
        }
    }

done:
    if (pUsers != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, pUsers);

    if (result != 0)
    {
        PrintMessageString(4381);
        ConPuts(StdOut, L"\n");
        PrintNetMessage(MSG_GROUP_SYNTAX);
    }

    return result;
}