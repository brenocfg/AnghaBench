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
struct TYPE_4__ {int wYear; int wDay; int wMonth; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 int /*<<< orphan*/  ReadNumber (int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  ReadSeparator (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SetLocalTime (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int** awMonths ; 
 int nDateFormat ; 

__attribute__((used)) static BOOL
ParseDate (LPTSTR s)
{
    SYSTEMTIME d;
    unsigned char leap;
    LPTSTR p = s;

    if (!*s)
        return TRUE;

    GetLocalTime (&d);

    d.wYear = 0;
    d.wDay = 0;
    d.wMonth = 0;

    switch (nDateFormat)
    {
        case 0: /* mmddyy */
        default:
            if (!ReadNumber (&p, &d.wMonth))
                return FALSE;
            if (!ReadSeparator (&p))
                return FALSE;
            if (!ReadNumber (&p, &d.wDay))
                return FALSE;
            if (!ReadSeparator (&p))
                return FALSE;
            if (!ReadNumber (&p, &d.wYear))
                return FALSE;
            break;

        case 1: /* ddmmyy */
            if (!ReadNumber (&p, &d.wDay))
                return FALSE;
            if (!ReadSeparator (&p))
                return FALSE;
            if (!ReadNumber (&p, &d.wMonth))
                return FALSE;
            if (!ReadSeparator (&p))
                return FALSE;
            if (!ReadNumber (&p, &d.wYear))
                return FALSE;
            break;

        case 2: /* yymmdd */
            if (!ReadNumber (&p, &d.wYear))
                return FALSE;
            if (!ReadSeparator (&p))
                return FALSE;
            if (!ReadNumber (&p, &d.wMonth))
                return FALSE;
            if (!ReadSeparator (&p))
                return FALSE;
            if (!ReadNumber (&p, &d.wDay))
                return FALSE;
            break;
    }

    /* if only entered two digits: */
    /*   assume 2000's if value less than 80 */
    /*   assume 1900's if value greater or equal 80 */
    if (d.wYear <= 99)
    {
        if (d.wYear >= 80)
            d.wYear = 1900 + d.wYear;
        else
            d.wYear = 2000 + d.wYear;
    }

    leap = (!(d.wYear % 4) && (d.wYear % 100)) || !(d.wYear % 400);

    if ((d.wMonth >= 1 && d.wMonth <= 12) &&
        (d.wDay >= 1 && d.wDay <= awMonths[leap][d.wMonth]) &&
        (d.wYear >= 1980 && d.wYear <= 2099))
    {
        SetLocalTime (&d);
        return TRUE;
    }

    return FALSE;
}