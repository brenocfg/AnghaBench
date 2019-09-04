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
typedef  int* PWSTR ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int GetCurrentDirectoryW (int,int*) ; 
 int /*<<< orphan*/  GetDirectoryStructure (int*,int,char*) ; 
 int /*<<< orphan*/  GetVolumeInformationW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDS_FOLDER_PATH ; 
 int /*<<< orphan*/  IDS_NO_SUBDIRECTORIES ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  IDS_VOL_SERIAL ; 
 scalar_t__ SetCurrentDirectoryW (int*) ; 
 int /*<<< orphan*/  StdOut ; 
 void* TRUE ; 
 void* bShowFiles ; 
 void* bUseAscii ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (int) ; 
 int towlower (int) ; 
 int /*<<< orphan*/  wcscpy (int*,int*) ; 
 int /*<<< orphan*/  wcstok (int*,char*) ; 

int wmain(int argc, WCHAR* argv[])
{
    DWORD dwSerial = 0;
    WCHAR t = 0;
    PWSTR strPath = NULL;
    DWORD sz = 0;
    //PWSTR context = NULL;
    PWSTR driveLetter = NULL;

    int i;

    /* Initialize the Console Standard Streams */
    ConInitStdStreams();

    /* Parse the command line */
    for (i = 1; i < argc; ++i)
    {
        if (argv[i][0] == L'-' || argv[i][0] == L'/')
        {
            switch (towlower(argv[i][1]))
            {
                case L'?':
                    /* Print help and exit after */
                    ConResPuts(StdOut, IDS_USAGE);
                    return 0;

                case L'f':
                    bShowFiles = TRUE;
                    break;

                case L'a':
                    bUseAscii = TRUE;
                    break;

                default:
                    break;
            }
        }
        else
        {
            /* This must be path to some folder */

            /* Set the current directory for this executable */
            BOOL b = SetCurrentDirectoryW(argv[i]);
            if (b == FALSE)
            {
                ConResPuts(StdOut, IDS_NO_SUBDIRECTORIES);
                return 1;
            }
        }
    }

    ConResPuts(StdOut, IDS_FOLDER_PATH);

    GetVolumeInformationW(NULL, NULL, 0, &dwSerial, NULL, NULL, NULL, 0);
    ConResPrintf(StdOut, IDS_VOL_SERIAL, dwSerial >> 16, dwSerial & 0xffff);

    /* get the buffer size */
    sz = GetCurrentDirectoryW(1, &t);
    /* must not return before calling delete[] */
    strPath = (PWSTR)malloc(sz * sizeof(WCHAR));

    /* get the current directory */
    GetCurrentDirectoryW(sz, strPath);

    /* get the drive letter , must not return before calling delete[] */
    driveLetter = (PWSTR)malloc(sz * sizeof(WCHAR));

    /* As we do not seem to have the _s functions properly set up, use the non-secure version for now */
    //wcscpy_s(driveLetter,sz,strPath);
    //wcstok_s(driveLetter,L":", &context); //parse for the drive letter
    wcscpy(driveLetter, strPath);
    wcstok(driveLetter, L":");

    ConPrintf(StdOut, L"%s:.\n", driveLetter);

    free(driveLetter);

    /* get the sub-directories within this current folder */
    GetDirectoryStructure(strPath, 1, L"          ");

    free(strPath);
    ConPuts(StdOut, L"\n");

    return 0;
}