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
struct TYPE_3__ {int /*<<< orphan*/  TimezoneInfo; int /*<<< orphan*/  DaylightName; int /*<<< orphan*/  StandardName; int /*<<< orphan*/  Description; } ;
typedef  TYPE_1__* PTIMEZONE_ENTRY ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ RegQueryValueExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static
LONG
QueryTimezoneData(
    HKEY hZoneKey,
    PTIMEZONE_ENTRY Entry)
{
    DWORD dwValueSize;
    LONG lError;

    dwValueSize = sizeof(Entry->Description);
    lError = RegQueryValueExW(hZoneKey,
                              L"Display",
                              NULL,
                              NULL,
                              (LPBYTE)&Entry->Description,
                              &dwValueSize);
    if (lError != ERROR_SUCCESS)
        return lError;

    dwValueSize = sizeof(Entry->StandardName);
    lError = RegQueryValueExW(hZoneKey,
                              L"Std",
                              NULL,
                              NULL,
                              (LPBYTE)&Entry->StandardName,
                              &dwValueSize);
    if (lError != ERROR_SUCCESS)
        return lError;

    dwValueSize = sizeof(Entry->DaylightName);
    lError = RegQueryValueExW(hZoneKey,
                              L"Dlt",
                              NULL,
                              NULL,
                              (LPBYTE)&Entry->DaylightName,
                              &dwValueSize);
    if (lError != ERROR_SUCCESS)
        return lError;

    dwValueSize = sizeof(Entry->TimezoneInfo);
    lError = RegQueryValueExW(hZoneKey,
                              L"TZI",
                              NULL,
                              NULL,
                              (LPBYTE)&Entry->TimezoneInfo,
                              &dwValueSize);
    return lError;
}