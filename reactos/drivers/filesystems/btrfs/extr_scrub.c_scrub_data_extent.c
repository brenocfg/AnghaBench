#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ sector_size; } ;
struct TYPE_6__ {TYPE_1__ superblock; } ;
typedef  TYPE_2__ device_extension ;
typedef  int /*<<< orphan*/  chunk ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ RtlFindFirstRunClear (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ RtlFindNextForwardRunClear (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 scalar_t__ SCRUB_UNIT ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ UInt32x32To64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  scrub_extent (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static NTSTATUS scrub_data_extent(device_extension* Vcb, chunk* c, uint64_t offset, ULONG type, uint32_t* csum, RTL_BITMAP* bmp, ULONG bmplen) {
    NTSTATUS Status;
    ULONG runlength, index;

    runlength = RtlFindFirstRunClear(bmp, &index);

    while (runlength != 0) {
        if (index >= bmplen)
            break;

        if (index + runlength >= bmplen) {
            runlength = bmplen - index;

            if (runlength == 0)
                break;
        }

        do {
            ULONG rl;

            if (runlength * Vcb->superblock.sector_size > SCRUB_UNIT)
                rl = SCRUB_UNIT / Vcb->superblock.sector_size;
            else
                rl = runlength;

            Status = scrub_extent(Vcb, c, type, offset + UInt32x32To64(index, Vcb->superblock.sector_size), rl * Vcb->superblock.sector_size, &csum[index]);
            if (!NT_SUCCESS(Status)) {
                ERR("scrub_data_extent_dup returned %08x\n", Status);
                return Status;
            }

            runlength -= rl;
            index += rl;
        } while (runlength > 0);

        runlength = RtlFindNextForwardRunClear(bmp, index, &index);
    }

    return STATUS_SUCCESS;
}