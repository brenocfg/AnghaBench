#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* FirstField; int /*<<< orphan*/ * Key; } ;
struct TYPE_6__ {int /*<<< orphan*/ * Line; } ;
struct TYPE_5__ {int /*<<< orphan*/ * Data; } ;
typedef  TYPE_2__* PINFCONTEXT ;
typedef  TYPE_3__* PINFCACHELINE ;
typedef  int /*<<< orphan*/ * PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
InfGetData (
    PINFCONTEXT Context,
    PCHAR *Key,
    PCHAR *Data)
{
    PINFCACHELINE CacheKey;

    if ((Context == NULL) || (Context->Line == NULL) || (Data == NULL))
    {
//      DPRINT("Invalid parameter\n");
        return FALSE;
    }

    CacheKey = (PINFCACHELINE)Context->Line;
    if (Key != NULL)
        *Key = CacheKey->Key;

    if (Data != NULL)
    {
        if (CacheKey->FirstField == NULL)
        {
            *Data = NULL;
        }
        else
        {
            *Data = CacheKey->FirstField->Data;
        }
    }

    return TRUE;
}