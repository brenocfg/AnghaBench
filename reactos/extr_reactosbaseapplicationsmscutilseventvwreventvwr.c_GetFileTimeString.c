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
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int LPWSTR ;
typedef  int /*<<< orphan*/  LPFILETIME ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_LONGDATE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FileTimeToLocalFileTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t) ; 
 int GetTimeFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  StringCchCopyExW (int,size_t,char*,int*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

BOOL
GetFileTimeString(LPFILETIME lpFileTime, LPWSTR pwszResult, UINT cchResult)
{
    FILETIME ft;
    SYSTEMTIME st;
    int cchWritten;
    size_t cchRemaining = cchResult;
    LPWSTR pwszEnd = pwszResult;

    if (!FileTimeToLocalFileTime(lpFileTime, &ft) || !FileTimeToSystemTime(&ft, &st))
        return FALSE;

    cchWritten = GetDateFormatW(LOCALE_USER_DEFAULT, DATE_LONGDATE, &st, NULL, pwszEnd, cchRemaining);
    if (cchWritten)
        --cchWritten; // GetDateFormatW returns count with terminating zero
    // else
        // ERR("GetDateFormatW failed\n");

    cchRemaining -= cchWritten;
    pwszEnd += cchWritten;

    StringCchCopyExW(pwszEnd, cchRemaining, L", ", &pwszEnd, &cchRemaining, 0);

    cchWritten = GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &st, NULL, pwszEnd, cchRemaining);
    if (cchWritten)
        --cchWritten; // GetTimeFormatW returns count with terminating zero
    // else
        // ERR("GetTimeFormatW failed\n");

    return TRUE;
}