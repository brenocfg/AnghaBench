#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_3__ {char* lpLocalName; char* lpRemoteName; int /*<<< orphan*/ * lpProvider; int /*<<< orphan*/  dwType; } ;
typedef  TYPE_1__ NETRESOURCE ;
typedef  char* LPWSTR ;
typedef  int INT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ARRAYSIZE (char*) ; 
 scalar_t__ CONNECT_LOCALDRIVE ; 
 int CONNECT_REDIRECT ; 
 int CONNECT_UPDATE_PROFILE ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ EnumerateConnections (char*) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IDS_USE_NOW_CONNECTED ; 
 scalar_t__ NO_ERROR ; 
 int /*<<< orphan*/  PrintError (scalar_t__) ; 
 int /*<<< orphan*/  PrintErrorMessage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintMessageStringV (int,char*) ; 
 int /*<<< orphan*/  RESOURCETYPE_DISK ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ValidateDeviceName (char*) ; 
 scalar_t__ WNetCancelConnection2 (char*,int,scalar_t__) ; 
 scalar_t__ WNetUseConnection (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,scalar_t__*,scalar_t__*) ; 
 char towupper (char) ; 
 scalar_t__ wcsicmp (char*,char*) ; 
 scalar_t__ wcslen (char*) ; 
 char* wcsstr (char*,char*) ; 

INT
cmdUse(
    INT argc,
    WCHAR **argv)
{
    DWORD Status, Len, Delete;

    if (argc == 2)
    {
        Status = EnumerateConnections(NULL);
        if (Status == NO_ERROR)
            PrintErrorMessage(ERROR_SUCCESS);
        else
            PrintError(Status);

        return 0;
    }
    else if (argc == 3)
    {
        if (!ValidateDeviceName(argv[2]))
        {
            PrintMessageStringV(3952, L"DeviceName");
            return 1;
        }

        Status = EnumerateConnections(argv[2]);
        if (Status == NO_ERROR)
            PrintErrorMessage(ERROR_SUCCESS);
        else
            PrintError(Status);

        return 0;
    }

    Delete = 0;
    if (wcsicmp(argv[2], L"/DELETE") == 0)
    {
        Delete = 3;
    }
    else
    {
        if ((argv[2][0] != '*' && argv[2][1] != 0) &&
            !ValidateDeviceName(argv[2]))
        {
            PrintMessageStringV(3952, L"DeviceName");
            return 1;
        }
    }

    if (wcsicmp(argv[3], L"/DELETE") == 0)
    {
        Delete = 2;
    }

    if (Delete != 0)
    {
        if (!ValidateDeviceName(argv[Delete]) || argv[Delete][0] == L'*')
        {
            PrintMessageStringV(3952, L"DeviceName");
            return 1;
        }

        Status = WNetCancelConnection2(argv[Delete], CONNECT_UPDATE_PROFILE, FALSE);
        if (Status != NO_ERROR)
            PrintError(Status);

        return Status;
    }
    else
    {
        BOOL Persist = FALSE;
        NETRESOURCE lpNet;
        WCHAR Access[256];
        DWORD OutFlags = 0, Size = ARRAYSIZE(Access);

        Len = wcslen(argv[3]);
        if (Len < 4)
        {
            PrintMessageStringV(3952, L"Name");
            return 1;
        }

        if (argv[3][0] != L'\\' || argv[3][1] != L'\\')
        {
            PrintMessageStringV(3952, L"Name");
            return 1;
        }

        if (argc > 4)
        {
            LPWSTR Cpy;
            Len = wcslen(argv[4]);
            if (Len > 12)
            {
                Cpy = HeapAlloc(GetProcessHeap(), 0, (Len + 1) * sizeof(WCHAR));
                if (Cpy)
                {
                    INT i;
                    for (i = 0; i < Len; ++i)
                        Cpy[i] = towupper(argv[4][i]);

                    if (wcsstr(Cpy, L"/PERSISTENT:") == Cpy)
                    {
                        LPWSTR Arg = Cpy + 12;
                        if (Len == 14 && Arg[0] == 'N' && Arg[1] == 'O')
                        {
                            Persist = FALSE;
                        }
                        else if (Len == 15 && Arg[0] == 'Y' && Arg[1] == 'E' && Arg[2] == 'S')
                        {
                            Persist = TRUE;
                        }
                        else
                        {
                            HeapFree(GetProcessHeap(), 0, Cpy);
                            PrintMessageStringV(3952, L"Persistent");
                            return 1;
                        }
                    }
                    HeapFree(GetProcessHeap(), 0, Cpy);
                }
            }

        }

        lpNet.dwType = RESOURCETYPE_DISK;
        lpNet.lpLocalName = (argv[2][0] != L'*') ? argv[2] : NULL;
        lpNet.lpRemoteName = argv[3];
        lpNet.lpProvider = NULL;

        Status = WNetUseConnection(NULL, &lpNet, NULL, NULL, CONNECT_REDIRECT | (Persist ? CONNECT_UPDATE_PROFILE : 0), Access, &Size, &OutFlags);
        if (argv[2][0] == L'*' && Status == NO_ERROR && OutFlags == CONNECT_LOCALDRIVE)
            ConResPrintf(StdOut, IDS_USE_NOW_CONNECTED, argv[3], Access);
        else if (Status != NO_ERROR)
            PrintError(Status);

        return Status;
    }
}