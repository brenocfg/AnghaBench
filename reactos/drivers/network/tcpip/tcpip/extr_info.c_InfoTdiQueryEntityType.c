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
typedef  int /*<<< orphan*/  ULONG ;
typedef  size_t UINT ;
struct TYPE_5__ {scalar_t__ tei_entity; scalar_t__ tei_instance; size_t flags; } ;
struct TYPE_4__ {scalar_t__ tei_entity; scalar_t__ tei_instance; } ;
typedef  int /*<<< orphan*/  TDI_STATUS ;
typedef  TYPE_1__ TDIEntityID ;
typedef  int /*<<< orphan*/  PUINT ;
typedef  int /*<<< orphan*/  PNDIS_BUFFER ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  KIRQL ;

/* Variables and functions */
 size_t EntityCount ; 
 TYPE_3__* EntityList ; 
 int /*<<< orphan*/  EntityListLock ; 
 int /*<<< orphan*/  InfoCopyOut (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TDI_INVALID_PARAMETER ; 
 int /*<<< orphan*/  TDI_SUCCESS ; 
 int /*<<< orphan*/  TcpipAcquireSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TcpipReleaseSpinLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

TDI_STATUS InfoTdiQueryEntityType(TDIEntityID ID,
                                  PNDIS_BUFFER Buffer,
				  PUINT BufferSize)
{
    KIRQL OldIrql;
    UINT i, Flags = 0;

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
        return TDI_INVALID_PARAMETER;
    }

    Flags = EntityList[i].flags;

    InfoCopyOut((PCHAR)&Flags,
                sizeof(ULONG),
                Buffer,
                BufferSize);

    TcpipReleaseSpinLock(&EntityListLock, OldIrql);

    return TDI_SUCCESS;
}