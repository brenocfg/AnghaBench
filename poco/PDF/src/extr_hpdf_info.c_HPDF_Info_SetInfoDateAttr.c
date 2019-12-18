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
struct TYPE_7__ {int month; int day; int hour; int minutes; int seconds; char ind; int off_hour; int off_minutes; int year; } ;
struct TYPE_6__ {int /*<<< orphan*/  mmgr; int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  scalar_t__ HPDF_InfoType ;
typedef  TYPE_1__* HPDF_Dict ;
typedef  TYPE_2__ HPDF_Date ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int HPDF_DATE_TIME_STR_LEN ; 
 int /*<<< orphan*/  HPDF_Dict_Add (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_INFO_MOD_DATE ; 
 int /*<<< orphan*/  HPDF_INVALID_DATE_TIME ; 
 int /*<<< orphan*/  HPDF_INVALID_PARAMETER ; 
 char* HPDF_IToA2 (char*,int,int) ; 
 scalar_t__ HPDF_MemCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HPDF_MemSet (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_String_New (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* InfoTypeToName (scalar_t__) ; 

HPDF_STATUS
HPDF_Info_SetInfoDateAttr (HPDF_Dict      info,
                           HPDF_InfoType  type,
                           HPDF_Date      value)
{
    char tmp[HPDF_DATE_TIME_STR_LEN + 1];
    char* ptmp;
    const char* name = InfoTypeToName (type);

    HPDF_PTRACE((" HPDF_Info_SetInfoDateAttr\n"));

    if (type > HPDF_INFO_MOD_DATE)
        return HPDF_SetError (info->error, HPDF_INVALID_PARAMETER, 0);

    HPDF_MemSet (tmp, 0, HPDF_DATE_TIME_STR_LEN + 1);
    if (value.month < 1 || 12 < value.month ||
        value.day < 1 ||
        23 < value.hour ||
        59 < value.minutes ||
        59 < value.seconds ||
        (value.ind != '+' && value.ind != '-' && value.ind != 'Z' &&
                value.ind != ' ') ||
        23 < value.off_hour ||
        59 < value.off_minutes) {
        return HPDF_SetError (info->error, HPDF_INVALID_DATE_TIME, 0);
    }

    switch (value.month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (value.day > 31)
                return HPDF_SetError (info->error, HPDF_INVALID_DATE_TIME, 0);

            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (value.day > 30)
                return HPDF_SetError (info->error, HPDF_INVALID_DATE_TIME, 0);

            break;
        case 2:
            if (value.day > 29 || (value.day == 29 &&
                (value.year % 4 != 0 ||
                (value.year % 100 == 0 && value.year % 400 != 0))))
                return HPDF_SetError (info->error, HPDF_INVALID_DATE_TIME, 0);

            break;
        default:
            return HPDF_SetError (info->error, HPDF_INVALID_DATE_TIME, 0);
    }

    ptmp = (char *)HPDF_MemCpy ((HPDF_BYTE *)tmp, (HPDF_BYTE *)"D:", 2);
    ptmp = HPDF_IToA2 (ptmp, value.year, 5);
    ptmp = HPDF_IToA2 (ptmp, value.month, 3);
    ptmp = HPDF_IToA2 (ptmp, value.day, 3);
    ptmp = HPDF_IToA2 (ptmp, value.hour, 3);
    ptmp = HPDF_IToA2 (ptmp, value.minutes, 3);
    ptmp = HPDF_IToA2 (ptmp, value.seconds, 3);
    if (value.ind != ' ') {
        *ptmp++ = value.ind;
        ptmp = HPDF_IToA2 (ptmp, value.off_hour, 3);
        *ptmp++ = '\'';
        ptmp = HPDF_IToA2 (ptmp, value.off_minutes, 3);
        *ptmp++ = '\'';
    }
    *ptmp = 0;

    return HPDF_Dict_Add (info, name, HPDF_String_New (info->mmgr, tmp,
                NULL));
}