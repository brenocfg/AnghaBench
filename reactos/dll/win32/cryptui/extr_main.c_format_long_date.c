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
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  FILETIME ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileTimeToSystemTime (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int GetDateFormatW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOCALE_SLONGDATE ; 
 int /*<<< orphan*/  LOCALE_SYSTEM_DEFAULT ; 

__attribute__((used)) static WCHAR *format_long_date(const FILETIME *fileTime)
{
    WCHAR dateFmt[80]; /* long enough for LOCALE_SLONGDATE */
    DWORD len;
    WCHAR *buf = NULL;
    SYSTEMTIME sysTime;

    /* FIXME: format isn't quite right, want time too */
    GetLocaleInfoW(LOCALE_SYSTEM_DEFAULT, LOCALE_SLONGDATE, dateFmt, ARRAY_SIZE(dateFmt));
    FileTimeToSystemTime(fileTime, &sysTime);
    len = GetDateFormatW(LOCALE_SYSTEM_DEFAULT, 0, &sysTime, dateFmt, NULL, 0);
    if (len)
    {
        buf = HeapAlloc(GetProcessHeap(), 0, len * sizeof(WCHAR));
        if (buf)
            GetDateFormatW(LOCALE_SYSTEM_DEFAULT, 0, &sysTime, dateFmt, buf,
             len);
    }
    return buf;
}