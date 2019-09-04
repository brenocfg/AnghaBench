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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  char* INT ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  IDS_DEVICE_STATUS_HEADER ; 
 int /*<<< orphan*/  IDS_ERROR_QUERY_DEVICES_FORM ; 
 int /*<<< orphan*/  IDS_PRINTER_OUTPUT_NOT_REROUTED ; 
 int /*<<< orphan*/  IDS_PRINTER_OUTPUT_REROUTED_SERIAL ; 
 int MAX_PORTNAME_LEN ; 
 scalar_t__ QueryDosDeviceW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  UnderlinedResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * wcsrchr (int /*<<< orphan*/ *,int) ; 

int ShowParallelStatus(INT nPortNum)
{
    WCHAR buffer[250];
    WCHAR szPortName[MAX_PORTNAME_LEN];

    swprintf(szPortName, L"LPT%d", nPortNum);

    ConPuts(StdOut, L"\n");
    UnderlinedResPrintf(StdOut, IDS_DEVICE_STATUS_HEADER, szPortName);
    ConPuts(StdOut, L"\n");

    if (QueryDosDeviceW(szPortName, buffer, ARRAYSIZE(buffer)))
    {
        PWSTR ptr = wcsrchr(buffer, L'\\');
        if (ptr != NULL)
        {
            if (_wcsicmp(szPortName, ++ptr) == 0)
                ConResPuts(StdOut, IDS_PRINTER_OUTPUT_NOT_REROUTED);
            else
                ConResPrintf(StdOut, IDS_PRINTER_OUTPUT_REROUTED_SERIAL, ptr);

            return 0;
        }
        else
        {
            ConResPrintf(StdErr, IDS_ERROR_QUERY_DEVICES_FORM, szPortName, buffer);
        }
    }
    else
    {
        ConPrintf(StdErr, L"ERROR: QueryDosDeviceW(%s) failed: 0x%lx\n", szPortName, GetLastError());
    }
    ConPuts(StdOut, L"\n");

    return 1;
}