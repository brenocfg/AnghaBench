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
typedef  int /*<<< orphan*/  VOID ;
typedef  size_t ULONG ;
struct TYPE_2__ {size_t tei_entity; size_t tei_instance; size_t flags; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  KIRQL ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 size_t EntityCount ; 
 TYPE_1__* EntityList ; 
 int /*<<< orphan*/  EntityListLock ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

VOID AddEntity(ULONG EntityType, PVOID Context, ULONG Flags)
{
    KIRQL OldIrql;
    ULONG i, Instance = 0;
    BOOLEAN ChoseIndex = FALSE;

    TcpipAcquireSpinLock(&EntityListLock, &OldIrql);

    while (!ChoseIndex)
    {
         ChoseIndex = TRUE;
         for (i = 0; i < EntityCount; i++)
         {
             if (EntityList[i].tei_entity == EntityType &&
                 EntityList[i].tei_instance == Instance)
             {
                 Instance++;
                 ChoseIndex = FALSE;
             }
         }
    }

    EntityList[EntityCount].tei_entity = EntityType;
    EntityList[EntityCount].tei_instance = Instance;
    EntityList[EntityCount].context = Context;
    EntityList[EntityCount].flags = Flags;
    EntityCount++;

    TcpipReleaseSpinLock(&EntityListLock, OldIrql);
}