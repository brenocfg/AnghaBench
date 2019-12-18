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
struct TYPE_4__ {int wHour; int wMinute; int wSecond; int wMilliseconds; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  scalar_t__* LPTSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetLocalTime (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLocalTime (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _T (char) ; 
 scalar_t__ _istdigit (scalar_t__) ; 
 scalar_t__ _totupper (scalar_t__) ; 
 scalar_t__ cDecimalSeparator ; 
 scalar_t__ cTimeSeparator ; 
 scalar_t__ nTimeFormat ; 

__attribute__((used)) static BOOL ParseTime (LPTSTR s)
{
    SYSTEMTIME t;
    LPTSTR p = s;

    if (!*s)
        return TRUE;

    GetLocalTime (&t);
    t.wHour = 0;
    t.wMinute = 0;
    t.wSecond = 0;
    t.wMilliseconds = 0;

    // first get hour
    if (_istdigit(*p))
    {
        while (_istdigit(*p))
        {
            t.wHour = t.wHour * 10 + *p - _T('0');
            p++;
        }
    }
    else
        return FALSE;

    // get time separator
    if (*p != cTimeSeparator)
        return FALSE;
    p++;

    // now get minutes
    if (_istdigit(*p))
    {
        while (_istdigit(*p))
        {
            t.wMinute = t.wMinute * 10 + *p - _T('0');
            p++;
        }
    }
    else
        return FALSE;

    // get time separator
    if (*p != cTimeSeparator)
        return FALSE;
    p++;

    // now get seconds
    if (_istdigit(*p))
    {
        while (_istdigit(*p))
        {
            t.wSecond = t.wSecond * 10 + *p - _T('0');
            p++;
        }
    }
    else
        return FALSE;

    // get decimal separator
    if (*p == cDecimalSeparator)
    {
        p++;

        // now get hundreths
        if (_istdigit(*p))
        {
            while (_istdigit(*p))
            {
                // t.wMilliseconds = t.wMilliseconds * 10 + *p - _T('0');
                p++;
            }
            // t.wMilliseconds *= 10;
        }
    }

    /* special case: 12 hour format */
    if (nTimeFormat == 0)
    {
        if (_totupper(*s) == _T('P'))
        {
            t.wHour += 12;
        }

        if ((_totupper(*s) == _T('A')) && (t.wHour == 12))
        {
            t.wHour = 0;
        }
    }

    if (t.wHour > 23 || t.wMinute > 60 || t.wSecond > 60 || t.wMilliseconds > 999)
        return FALSE;

    SetLocalTime (&t);

    return TRUE;
}