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

/* Variables and functions */
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int DWNL_E_LASTERROR ; 
#define  DWNL_E_NEEDTARGETFILENAME 129 
#define  DWNL_E_UNSUPPORTEDSCHEME 128 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  IDS_ERROR_CODE ; 
 int /*<<< orphan*/  IDS_ERROR_DOWNLOAD ; 
 int /*<<< orphan*/  IDS_ERROR_FILENAME ; 
 int /*<<< orphan*/  IDS_ERROR_PROTOCOL ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  write_status (char*) ; 

__attribute__((used)) static int
print_err(int iErr)
{
    write_status(L"");

    if (iErr == DWNL_E_LASTERROR)
    {
        if (GetLastError() == ERROR_SUCCESS)
        {
            /* File not found */
            ConResPrintf(StdErr, IDS_ERROR_DOWNLOAD);
        }
        else
        {
            /* Display last error code */
            ConResPrintf(StdErr, IDS_ERROR_CODE, GetLastError());
        }
    }
    else
    {
        switch (iErr)
        {
            case DWNL_E_NEEDTARGETFILENAME:
                ConResPrintf(StdErr, IDS_ERROR_FILENAME);
                break;

            case DWNL_E_UNSUPPORTEDSCHEME:
                ConResPrintf(StdErr, IDS_ERROR_PROTOCOL);
                break;
        }
    }

    return 1;
}