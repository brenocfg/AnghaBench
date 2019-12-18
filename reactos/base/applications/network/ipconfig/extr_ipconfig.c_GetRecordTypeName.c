#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_2__ {scalar_t__ wRecordType; int /*<<< orphan*/ * pszRecordName; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  size_t INT ;

/* Variables and functions */
 TYPE_1__* TypeArray ; 
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _stprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

LPTSTR
GetRecordTypeName(WORD wType)
{
    static TCHAR szType[8];
    INT i;

    for (i = 0; ; i++)
    {
         if (TypeArray[i].pszRecordName == NULL)
             break;

         if (TypeArray[i].wRecordType == wType)
             return TypeArray[i].pszRecordName;
    }

    _stprintf(szType, _T("%hu"), wType);

    return szType;
}