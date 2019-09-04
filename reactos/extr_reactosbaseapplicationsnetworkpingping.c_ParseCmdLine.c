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
typedef  void* ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  Ttl; int /*<<< orphan*/  Flags; } ;
typedef  int* PWSTR ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 void* DEFAULT_TIMEOUT ; 
 void* FALSE ; 
 int /*<<< orphan*/  Family ; 
 int /*<<< orphan*/  IDS_BAD_OPTION ; 
 int /*<<< orphan*/  IDS_BAD_PARAMETER ; 
 int /*<<< orphan*/  IDS_BAD_VALUE ; 
 int /*<<< orphan*/  IDS_MISSING_ADDRESS ; 
 int /*<<< orphan*/  IDS_MISSING_VALUE ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  IDS_WRONG_FAMILY ; 
 int /*<<< orphan*/  IP_FLAG_DF ; 
 TYPE_1__ IpOptions ; 
 void* MAX_SEND_SIZE ; 
 void* PingCount ; 
 void* PingForever ; 
 void* RequestSize ; 
 void* ResolveAddress ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 void* TRUE ; 
 int* TargetName ; 
 void* Timeout ; 
 void* UCHAR_MAX ; 
 int /*<<< orphan*/  UINT_MAX ; 
 void* wcstoul (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL
ParseCmdLine(int argc, PWSTR argv[])
{
    int i;

    if (argc < 2)
    {
        ConResPrintf(StdOut, IDS_USAGE);
        return FALSE;
    }

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == L'-' || argv[i][0] == L'/')
        {
            switch (argv[i][1])
            {
            case L't':
                PingForever = TRUE;
                break;

            case L'a':
                ResolveAddress = TRUE;
                break;

            case L'n':
            {
                if (i + 1 < argc)
                {
                    PingForever = FALSE;
                    PingCount = wcstoul(argv[++i], NULL, 0);
                    if (PingCount == 0)
                    {
                        ConResPrintf(StdErr, IDS_BAD_VALUE, argv[i - 1], 1, UINT_MAX);
                        return FALSE;
                    }
                }
                else
                {
                    ConResPrintf(StdErr, IDS_MISSING_VALUE, argv[i]);
                    return FALSE;
                }
                break;
            }

            case L'l':
            {
                if (i + 1 < argc)
                {
                    RequestSize = wcstoul(argv[++i], NULL, 0);
                    if (RequestSize > MAX_SEND_SIZE)
                    {
                        ConResPrintf(StdErr, IDS_BAD_VALUE, argv[i - 1], 0, MAX_SEND_SIZE);
                        return FALSE;
                    }
                }
                else
                {
                    ConResPrintf(StdErr, IDS_MISSING_VALUE, argv[i]);
                    return FALSE;
                }
                break;
            }

            case L'f':
            {
                if (Family == AF_INET6)
                {
                    ConResPrintf(StdErr, IDS_WRONG_FAMILY, argv[i], L"IPv4");
                    return FALSE;
                }

                Family = AF_INET;
                IpOptions.Flags |= IP_FLAG_DF;
                break;
            }

            case L'i':
            {
                if (i + 1 < argc)
                {
                    ULONG Ttl = wcstoul(argv[++i], NULL, 0);

                    if ((Ttl == 0) || (Ttl > UCHAR_MAX))
                    {
                        ConResPrintf(StdErr, IDS_BAD_VALUE, argv[i - 1], 1, UCHAR_MAX);
                        return FALSE;
                    }

                    IpOptions.Ttl = (UCHAR)Ttl;
                }
                else
                {
                    ConResPrintf(StdErr, IDS_MISSING_VALUE, argv[i]);
                    return FALSE;
                }
                break;
            }

            case L'v':
            {
                if (Family == AF_INET6)
                {
                    ConResPrintf(StdErr, IDS_WRONG_FAMILY, argv[i], L"IPv4");
                    return FALSE;
                }

                Family = AF_INET;

                if (i + 1 < argc)
                {
                    /* This option has been deprecated. Don't do anything. */
                    i++;
                }
                else
                {
                    ConResPrintf(StdErr, IDS_MISSING_VALUE, argv[i]);
                    return FALSE;
                }

                break;
            }

            case L'w':
            {
                if (i + 1 < argc)
                {
                    Timeout = wcstoul(argv[++i], NULL, 0);
                    if (Timeout < DEFAULT_TIMEOUT)
                        Timeout = DEFAULT_TIMEOUT;
                }
                else
                {
                    ConResPrintf(StdErr, IDS_MISSING_VALUE, argv[i]);
                    return FALSE;
                }
                break;
            }

            case L'R':
            {
                if (Family == AF_INET)
                {
                    ConResPrintf(StdErr, IDS_WRONG_FAMILY, argv[i], L"IPv6");
                    return FALSE;
                }

                Family = AF_INET6;

                /* This option has been deprecated. Don't do anything. */
                break;
            }

            case L'4':
            {
                if (Family == AF_INET6)
                {
                    ConResPrintf(StdErr, IDS_WRONG_FAMILY, argv[i], L"IPv4");
                    return FALSE;
                }

                Family = AF_INET;
                break;
            }

            case L'6':
            {
                if (Family == AF_INET)
                {
                    ConResPrintf(StdErr, IDS_WRONG_FAMILY, argv[i], L"IPv6");
                    return FALSE;
                }

                Family = AF_INET6;
                break;
            }

            case L'?':
                ConResPrintf(StdOut, IDS_USAGE);
                return FALSE;

            default:
                ConResPrintf(StdErr, IDS_BAD_OPTION, argv[i]);
                ConResPrintf(StdErr, IDS_USAGE);
                return FALSE;
            }
        }
        else
        {
            if (TargetName != NULL)
            {
                ConResPrintf(StdErr, IDS_BAD_PARAMETER, argv[i]);
                return FALSE;
            }

            TargetName = argv[i];
        }
    }

    if (TargetName == NULL)
    {
        ConResPrintf(StdErr, IDS_MISSING_ADDRESS);
        return FALSE;
    }

    return TRUE;
}