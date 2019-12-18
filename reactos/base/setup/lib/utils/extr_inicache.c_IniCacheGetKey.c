#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * Data; } ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/ * PINICACHESECTION ;
typedef  TYPE_1__* PINICACHEKEY ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 TYPE_1__* IniCacheFindKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 int /*<<< orphan*/  wcslen (int /*<<< orphan*/ *) ; 

NTSTATUS
IniCacheGetKey(
    PINICACHESECTION Section,
    PWCHAR KeyName,
    PWCHAR *KeyData)
{
    PINICACHEKEY Key;

    if (Section == NULL || KeyName == NULL || KeyData == NULL)
    {
        DPRINT("Invalid parameter\n");
        return STATUS_INVALID_PARAMETER;
    }

    *KeyData = NULL;

    Key = IniCacheFindKey(Section, KeyName, wcslen(KeyName));
    if (Key == NULL)
    {
        return STATUS_INVALID_PARAMETER;
    }

    *KeyData = Key->Data;

    return STATUS_SUCCESS;
}