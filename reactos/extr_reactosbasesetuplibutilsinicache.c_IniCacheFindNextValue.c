#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* Key; } ;
struct TYPE_4__ {int /*<<< orphan*/  Data; int /*<<< orphan*/  Name; struct TYPE_4__* Next; } ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  TYPE_1__* PINICACHEKEY ;
typedef  TYPE_2__* PINICACHEITERATOR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
IniCacheFindNextValue(
    PINICACHEITERATOR Iterator,
    PWCHAR *KeyName,
    PWCHAR *KeyData)
{
    PINICACHEKEY Key;

    if (Iterator == NULL || KeyName == NULL || KeyData == NULL)
    {
        DPRINT("Invalid parameter\n");
        return FALSE;
    }

    Key = Iterator->Key->Next;
    if (Key == NULL)
    {
        DPRINT("No more entries\n");
        return FALSE;
    }

    *KeyName = Key->Name;
    *KeyData = Key->Data;

    Iterator->Key = Key;

    return TRUE;
}