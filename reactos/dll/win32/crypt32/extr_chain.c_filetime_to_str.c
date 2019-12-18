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
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  char* LPCSTR ;
typedef  int /*<<< orphan*/  FILETIME ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateFormatA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLocaleInfoA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCALE_SSHORTDATE ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 
 char* wine_dbg_sprintf (char*,char*) ; 

__attribute__((used)) static LPCSTR filetime_to_str(const FILETIME *time)
{
    char date[80];
    char dateFmt[80]; /* sufficient for all versions of LOCALE_SSHORTDATE */
    SYSTEMTIME sysTime;

    if (!time) return "(null)";

    GetLocaleInfoA(LOCALE_SYSTEM_DEFAULT, LOCALE_SSHORTDATE, dateFmt, ARRAY_SIZE(dateFmt));
    FileTimeToSystemTime(time, &sysTime);
    GetDateFormatA(LOCALE_SYSTEM_DEFAULT, 0, &sysTime, dateFmt, date, ARRAY_SIZE(date));
    return wine_dbg_sprintf("%s", date);
}