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
typedef  int WCHAR ;
typedef  int INT ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  StdOut ; 
 void* TRUE ; 
 void* bAdhoc ; 
 void* bConnect ; 
 void* bDisconnect ; 
 void* bScan ; 
 int* sSsid ; 
 int* sWepKey ; 

BOOL ParseCmdline(int argc, WCHAR *argv[])
{
    INT i;

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == L'-')
        {
            switch (argv[i][1])
            {
                case L's':
                    bScan = TRUE;
                    break;
                case L'd':
                    bDisconnect = TRUE;
                    break;
                case L'c':
                    if (i == argc - 1)
                    {
                        ConResPuts(StdOut, IDS_USAGE);
                        return FALSE;
                    }
                    bConnect = TRUE;
                    sSsid = argv[++i];
                    break;
                case L'w':
                    if (i == argc - 1)
                    {
                        ConResPuts(StdOut, IDS_USAGE);
                        return FALSE;
                    }
                    sWepKey = argv[++i];
                    break;
                case L'a':
                    bAdhoc = TRUE;
                    break;
                default :
                    ConResPuts(StdOut, IDS_USAGE);
                    return FALSE;
            }

        }
        else
        {
            ConResPuts(StdOut, IDS_USAGE);
            return FALSE;
        }
    }

    return TRUE;
}