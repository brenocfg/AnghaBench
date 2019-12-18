#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dwHighDateTime; int /*<<< orphan*/  dwLowDateTime; } ;
struct TYPE_10__ {int /*<<< orphan*/  HighPart; int /*<<< orphan*/  LowPart; } ;
struct TYPE_12__ {TYPE_1__ u; } ;
struct TYPE_11__ {int wMonth; int wDay; int wYear; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  int /*<<< orphan*/ * PWSTR ;
typedef  int /*<<< orphan*/  PULONG ;
typedef  TYPE_3__ LARGE_INTEGER ;
typedef  int INT ;
typedef  TYPE_4__ FILETIME ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLocaleInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LOCALE_IDATE ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  LocalFileTimeToFileTime (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ReadNumber (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ReadSeparator (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  RtlTimeToSecondsSince1970 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemTimeToFileTime (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static
BOOL
ParseDate(
    PWSTR s,
    PULONG pSeconds)
{
    SYSTEMTIME SystemTime = {0};
    FILETIME LocalFileTime, FileTime;
    LARGE_INTEGER Time;
    INT nDateFormat = 0;
    PWSTR p = s;

    if (!*s)
        return FALSE;

    GetLocaleInfoW(LOCALE_USER_DEFAULT,
                   LOCALE_IDATE,
                   (PWSTR)&nDateFormat,
                   sizeof(INT));

    switch (nDateFormat)
    {
        case 0: /* mmddyy */
        default:
            if (!ReadNumber(&p, &SystemTime.wMonth))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wDay))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wYear))
                return FALSE;
            break;

        case 1: /* ddmmyy */
            if (!ReadNumber(&p, &SystemTime.wDay))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wMonth))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wYear))
                return FALSE;
            break;

        case 2: /* yymmdd */
            if (!ReadNumber(&p, &SystemTime.wYear))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wMonth))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wDay))
                return FALSE;
            break;
    }

    /* if only entered two digits: */
    /*   assume 2000's if value less than 80 */
    /*   assume 1900's if value greater or equal 80 */
    if (SystemTime.wYear <= 99)
    {
        if (SystemTime.wYear >= 80)
            SystemTime.wYear += 1900;
        else
            SystemTime.wYear += 2000;
    }

    if (!SystemTimeToFileTime(&SystemTime, &LocalFileTime))
        return FALSE;

    if (!LocalFileTimeToFileTime(&LocalFileTime, &FileTime))
        return FALSE;

    Time.u.LowPart = FileTime.dwLowDateTime;
    Time.u.HighPart = FileTime.dwHighDateTime;

    if (!RtlTimeToSecondsSince1970(&Time, pSeconds))
        return FALSE;

    return TRUE;
}