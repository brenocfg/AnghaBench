#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int wYear; int wMonth; int wDay; int wHour; int wMinute; int wSecond; } ;
struct TYPE_10__ {int select; int nCharsEntered; int* fieldspec; int* charsEntered; TYPE_1__ date; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__ DATETIME_INFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DATETIME_IsDateInValidRange (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  DATETIME_SendDateTimeChangeNotify (TYPE_2__*) ; 
 scalar_t__ DATETIME_SetSystemTime (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int DTHT_DATEFIELD ; 
 scalar_t__ FALSE ; 
#define  FULLYEAR 145 
 int /*<<< orphan*/  GDT_VALID ; 
#define  INVALIDFULLYEAR 144 
 scalar_t__ MONTHCAL_MonthLength (int,int) ; 
#define  ONEDIGIT12HOUR 143 
#define  ONEDIGIT24HOUR 142 
#define  ONEDIGITDAY 141 
#define  ONEDIGITMINUTE 140 
#define  ONEDIGITMONTH 139 
#define  ONEDIGITSECOND 138 
#define  ONEDIGITYEAR 137 
#define  ONELETTERAMPM 136 
 scalar_t__ TRUE ; 
#define  TWODIGIT12HOUR 135 
#define  TWODIGIT24HOUR 134 
#define  TWODIGITDAY 133 
#define  TWODIGITMINUTE 132 
#define  TWODIGITMONTH 131 
#define  TWODIGITSECOND 130 
#define  TWODIGITYEAR 129 
#define  TWOLETTERAMPM 128 

__attribute__((used)) static void
DATETIME_ApplySelectedField (DATETIME_INFO *infoPtr)
{
    int fieldNum = infoPtr->select & DTHT_DATEFIELD;
    int i, val = 0;
    BOOL clamp_day = FALSE;
    SYSTEMTIME date = infoPtr->date;
    int oldyear;

    if (infoPtr->select == -1 || infoPtr->nCharsEntered == 0)
        return;

    if ((infoPtr->fieldspec[fieldNum] == ONELETTERAMPM) ||
        (infoPtr->fieldspec[fieldNum] == TWOLETTERAMPM))
        val = infoPtr->charsEntered[0];
    else {
        for (i=0; i<infoPtr->nCharsEntered; i++)
            val = val * 10 + infoPtr->charsEntered[i] - '0';
    }

    infoPtr->nCharsEntered = 0;

    switch (infoPtr->fieldspec[fieldNum]) {
        case ONEDIGITYEAR:
        case TWODIGITYEAR:
            oldyear = date.wYear;
            date.wYear = date.wYear - (date.wYear%100) + val;

            if (DATETIME_IsDateInValidRange(infoPtr, &date))
                clamp_day = TRUE;
            else
                date.wYear = oldyear;

            break;
        case INVALIDFULLYEAR:
        case FULLYEAR:
            oldyear = date.wYear;
            date.wYear = val;

            if (DATETIME_IsDateInValidRange(infoPtr, &date))
                clamp_day = TRUE;
            else
                date.wYear = oldyear;

            break;
        case ONEDIGITMONTH:
        case TWODIGITMONTH:
            date.wMonth = val;
            clamp_day = TRUE;
            break;
        case ONEDIGITDAY:
        case TWODIGITDAY:
            date.wDay = val;
            break;
        case ONEDIGIT12HOUR:
        case TWODIGIT12HOUR:
            if (val >= 24)
                val -= 20;

            if (val >= 13)
                date.wHour = val;
            else if (val != 0) {
                if (date.wHour >= 12) /* preserve current AM/PM state */
                    date.wHour = (val == 12 ? 12 : val + 12);
                else
                    date.wHour = (val == 12 ? 0 : val);
            }
            break;
        case ONEDIGIT24HOUR:
        case TWODIGIT24HOUR:
            date.wHour = val;
            break;
        case ONEDIGITMINUTE:
        case TWODIGITMINUTE:
            date.wMinute = val;
            break;
        case ONEDIGITSECOND:
        case TWODIGITSECOND:
            date.wSecond = val;
            break;
        case ONELETTERAMPM:
        case TWOLETTERAMPM:
            if (val == 'a' || val == 'A') {
                if (date.wHour >= 12)
                    date.wHour -= 12;
            } else if (val == 'p' || val == 'P') {
                if (date.wHour < 12)
                    date.wHour += 12;
            }
            break;
    }

    if (clamp_day && date.wDay > MONTHCAL_MonthLength(date.wMonth, date.wYear))
        date.wDay = MONTHCAL_MonthLength(date.wMonth, date.wYear);

    if (DATETIME_SetSystemTime(infoPtr, GDT_VALID, &date))
        DATETIME_SendDateTimeChangeNotify (infoPtr);
}