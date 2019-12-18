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
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int* LogName; } ;
typedef  int* PWSTR ;
typedef  TYPE_1__* PLOGFILE ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ AddNewEventSource (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  DumpEventSourceList () ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_MULTI_SZ ; 
 scalar_t__ RegEnumKeyExW (int /*<<< orphan*/ ,int,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegQueryInfoKeyW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StringCchCopyExW (int*,size_t,int*,int**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 scalar_t__ _wcsicmp (int*,int*) ; 
 int wcslen (int*) ; 

BOOL
LoadEventSources(HKEY hKey,
                 PLOGFILE pLogFile)
{
    BOOL Success;
    DWORD dwNumSubKeys, dwMaxSubKeyLength;
    DWORD dwEventSourceNameLength, MaxValueLen;
    DWORD dwIndex;
    PWSTR Buf = NULL, SourceList = NULL, Source = NULL;
    size_t cchRemaining = 0;
    LONG Result;

    DPRINT("LoadEventSources\n");

    Result = RegQueryInfoKeyW(hKey, NULL, NULL, NULL, &dwNumSubKeys, &dwMaxSubKeyLength,
                              NULL, NULL, NULL, NULL, NULL, NULL);
    if (Result != ERROR_SUCCESS)
    {
        DPRINT1("RegQueryInfoKeyW failed: %lu\n", Result);
        return FALSE;
    }

    dwMaxSubKeyLength++;

    Buf = HeapAlloc(GetProcessHeap(), 0, dwMaxSubKeyLength * sizeof(WCHAR));
    if (!Buf)
    {
        DPRINT1("Error: cannot allocate heap!\n");
        return FALSE;
    }

    /*
     * Allocate a buffer for storing the names of the sources as a REG_MULTI_SZ
     * in the registry. Also add the event log as its own source.
     * Add a final NULL-terminator.
     */
    MaxValueLen = dwNumSubKeys * dwMaxSubKeyLength + wcslen(pLogFile->LogName) + 2;
    SourceList = HeapAlloc(GetProcessHeap(), 0, MaxValueLen * sizeof(WCHAR));
    if (!SourceList)
    {
        DPRINT1("Error: cannot allocate heap!\n");
        /* It is not dramatic if we cannot create it */
    }
    else
    {
        cchRemaining = MaxValueLen;
        Source = SourceList;
    }

    /*
     * Enumerate all the subkeys of the event log key, that constitute
     * all the possible event sources for this event log. At this point,
     * skip the possible existing source having the same name as the
     * event log, it will be added later on.
     */
    dwEventSourceNameLength = dwMaxSubKeyLength;
    dwIndex = 0;
    while (RegEnumKeyExW(hKey,
                         dwIndex,
                         Buf,
                         &dwEventSourceNameLength,
                         NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        if (_wcsicmp(pLogFile->LogName, Buf) != 0)
        {
            DPRINT("Event Source: %S\n", Buf);
            Success = AddNewEventSource(pLogFile, Buf);
            if (Success && (Source != NULL))
            {
                /* Append the event source name and an extra NULL-terminator */
                StringCchCopyExW(Source, cchRemaining, Buf, &Source, &cchRemaining, 0);
                if (cchRemaining > 0)
                {
                    *++Source = L'\0';
                    cchRemaining--;
                }
            }
        }

        dwEventSourceNameLength = dwMaxSubKeyLength;
        dwIndex++;
    }

    /* Finally, allow the event log itself to be its own source */
    DPRINT("Event Source: %S\n", pLogFile->LogName);
    Success = AddNewEventSource(pLogFile, pLogFile->LogName);
    if (Success && (Source != NULL))
    {
        /* Append the event source name and an extra NULL-terminator */
        StringCchCopyExW(Source, cchRemaining, pLogFile->LogName, &Source, &cchRemaining, 0);
        if (cchRemaining > 0)
        {
            *++Source = L'\0';
            cchRemaining--;
        }
    }

    /* Save the list of sources in the registry */
    Result = RegSetValueExW(hKey,
                            L"Sources",
                            0,
                            REG_MULTI_SZ,
                            (LPBYTE)SourceList,
                            (MaxValueLen - cchRemaining + 1) * sizeof(WCHAR));
    if (Result != ERROR_SUCCESS)
    {
        DPRINT1("RegSetValueExW failed: %lu\n", Result);
    }

    if (SourceList)
        HeapFree(GetProcessHeap(), 0, SourceList);

    HeapFree(GetProcessHeap(), 0, Buf);

    DumpEventSourceList();

    return TRUE;
}