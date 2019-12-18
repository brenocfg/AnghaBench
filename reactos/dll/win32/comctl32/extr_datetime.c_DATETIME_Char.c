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
typedef  char WPARAM ;
struct TYPE_4__ {int select; int* fieldspec; char* charsEntered; int nCharsEntered; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ DATETIME_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DATETIME_ApplySelectedField (TYPE_1__*) ; 
 int DTHT_DATEFIELD ; 
 int FULLYEAR ; 
 int INVALIDFULLYEAR ; 
 int ONEDIGIT12HOUR ; 
 int ONEDIGIT24HOUR ; 
 int ONELETTERAMPM ; 
 int TWODIGIT12HOUR ; 
 int TWODIGIT24HOUR ; 
 int TWOLETTERAMPM ; 

__attribute__((used)) static LRESULT
DATETIME_Char (DATETIME_INFO *infoPtr, WPARAM vkCode)
{
    int fieldNum, fieldSpec;

    fieldNum = infoPtr->select & DTHT_DATEFIELD;
    fieldSpec = infoPtr->fieldspec[fieldNum];

    if (fieldSpec == ONELETTERAMPM || fieldSpec == TWOLETTERAMPM) {
        infoPtr->charsEntered[0] = vkCode;
        infoPtr->nCharsEntered = 1;

        DATETIME_ApplySelectedField(infoPtr);
    } else if (vkCode >= '0' && vkCode <= '9') {
        int maxChars;

        infoPtr->charsEntered[infoPtr->nCharsEntered++] = vkCode;

        if (fieldSpec == INVALIDFULLYEAR || fieldSpec == FULLYEAR)
            maxChars = 4;
        else
            maxChars = 2;

        if ((fieldSpec == ONEDIGIT12HOUR ||
             fieldSpec == TWODIGIT12HOUR ||
             fieldSpec == ONEDIGIT24HOUR ||
             fieldSpec == TWODIGIT24HOUR) &&
            (infoPtr->nCharsEntered == 1))
        {
            if (vkCode >= '3')
                 maxChars = 1;
        }

        if (maxChars == infoPtr->nCharsEntered)
            DATETIME_ApplySelectedField(infoPtr);
    }

    return 0;
}