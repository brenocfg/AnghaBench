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
typedef  int UINT ;
typedef  int /*<<< orphan*/  TIME_ZONE_INFORMATION ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DATE_SHORTDATE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  GetFileTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTimeFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  GetTimeZoneInformation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SystemTimeToTzSpecificLocalTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIME_FORCE24HOURFORMAT ; 

BOOL
GetFileModifyTime(LPCWSTR pFullPath, WCHAR * szTime, int szTimeSize)
{
    HANDLE hFile;
    FILETIME AccessTime;
    SYSTEMTIME SysTime, LocalTime;
    UINT Length;
    TIME_ZONE_INFORMATION TimeInfo;

    hFile = CreateFileW(pFullPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (!hFile)
        return FALSE;

    if (!GetFileTime(hFile, NULL, NULL, &AccessTime))
    {
        CloseHandle(hFile);
        return FALSE;
    }
    CloseHandle(hFile);

    if(!GetTimeZoneInformation(&TimeInfo))
        return FALSE;

    if (!FileTimeToSystemTime(&AccessTime, &SysTime))
        return FALSE;

    if (!SystemTimeToTzSpecificLocalTime(&TimeInfo, &SysTime, &LocalTime))
        return FALSE;

    Length = GetDateFormatW(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &LocalTime, NULL, szTime, szTimeSize);
    szTime[Length-1] = L' ';
    return GetTimeFormatW(LOCALE_USER_DEFAULT, TIME_FORCE24HOURFORMAT, &LocalTime, NULL, &szTime[Length], szTimeSize-Length);
}