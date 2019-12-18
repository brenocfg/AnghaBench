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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  DeviceId; } ;
struct TYPE_4__ {int /*<<< orphan*/  QuadPart; } ;
typedef  TYPE_1__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  scalar_t__ ARC_STATUS ;

/* Variables and functions */
 scalar_t__ ArcRead (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__*) ; 
 scalar_t__ ArcSeek (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* BtrFsInfo ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 scalar_t__ ESUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SeekAbsolute ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOLEAN disk_read(u64 physical, void *dest, u32 count)
{
    LARGE_INTEGER Position;
    ULONG Count;
    ARC_STATUS Status;

    if (!dest)
        return FALSE;

    Position.QuadPart = physical;
    Status = ArcSeek(BtrFsInfo->DeviceId, &Position, SeekAbsolute);
    if (Status != ESUCCESS)
    {
        ERR("ArcSeek returned status %lu\n", Status);
        return FALSE;
    }

    Status = ArcRead(BtrFsInfo->DeviceId, dest, count, &Count);
    if (Status != ESUCCESS || Count != count)
    {
        ERR("ArcRead returned status %lu\n", Status);
        return FALSE;
    }

    return TRUE;
}