#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {scalar_t__ tei_entity; scalar_t__ tei_instance; int /*<<< orphan*/ * context; } ;
struct TYPE_4__ {scalar_t__ tei_entity; scalar_t__ tei_instance; } ;
typedef  TYPE_1__ TDIEntityID ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,scalar_t__,scalar_t__) ; 
 size_t EntityCount ; 
 TYPE_3__* EntityList ; 
 int /*<<< orphan*/  EntityListLock ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

PVOID GetContext(TDIEntityID ID)
{
    UINT i;
    KIRQL OldIrql;
    PVOID Context;

    TcpipAcquireSpinLock(&EntityListLock, &OldIrql);

    for (i = 0; i < EntityCount; i++)
    {
        if (EntityList[i].tei_entity == ID.tei_entity &&
            EntityList[i].tei_instance == ID.tei_instance)
            break;
    }

    if (i == EntityCount)
    {
        TcpipReleaseSpinLock(&EntityListLock, OldIrql);
        DbgPrint("WARNING: Unable to get context for %d %d\n", ID.tei_entity, ID.tei_instance);
        return NULL;
    }

    Context = EntityList[i].context;

    TcpipReleaseSpinLock(&EntityListLock, OldIrql);

    return Context;
}