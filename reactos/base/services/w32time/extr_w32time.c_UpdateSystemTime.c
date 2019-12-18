#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_7__ {int QuadPart; } ;
struct TYPE_6__ {int wYear; int wMonth; int wDay; scalar_t__ wMilliseconds; scalar_t__ wSecond; scalar_t__ wMinute; scalar_t__ wHour; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int LONGLONG ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  scalar_t__ FILETIME ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  FileTimeToSystemTime (scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  SystemSetTime (TYPE_1__*) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (TYPE_1__*,scalar_t__*) ; 

__attribute__((used)) static DWORD
UpdateSystemTime(ULONG ulTime)
{
    FILETIME ftNew;
    LARGE_INTEGER li;
    SYSTEMTIME stNew;

    /* Time at 1st Jan 1900 */
    stNew.wYear = 1900;
    stNew.wMonth = 1;
    stNew.wDay = 1;
    stNew.wHour = 0;
    stNew.wMinute = 0;
    stNew.wSecond = 0;
    stNew.wMilliseconds = 0;

    /* Convert to a file time */
    if (!SystemTimeToFileTime(&stNew, &ftNew))
    {
        return GetLastError();
    }

    /* Add on the time passed since 1st Jan 1900 */
    li = *(LARGE_INTEGER *)&ftNew;
    li.QuadPart += (LONGLONG)10000000 * ulTime;
    ftNew = * (FILETIME *)&li;

    /* Convert back to a system time */
    if (!FileTimeToSystemTime(&ftNew, &stNew))
    {
        return GetLastError();
    }

    if (!SystemSetTime(&stNew))
    {
        return GetLastError();
    }

    return ERROR_SUCCESS;
}