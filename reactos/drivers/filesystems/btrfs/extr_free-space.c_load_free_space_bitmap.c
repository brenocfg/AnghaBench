#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int sector_size; } ;
struct TYPE_7__ {TYPE_1__ superblock; } ;
typedef  TYPE_2__ device_extension ;
struct TYPE_8__ {int /*<<< orphan*/  space_size; int /*<<< orphan*/  space; } ;
typedef  TYPE_3__ chunk ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  RTL_BITMAP ;

/* Variables and functions */
 int RtlFindFirstRunClear (int /*<<< orphan*/ *,int*) ; 
 int RtlFindNextForwardRunClear (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  RtlInitializeBitMap (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  add_space_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void load_free_space_bitmap(device_extension* Vcb, chunk* c, uint64_t offset, void* data, uint64_t* total_space) {
    RTL_BITMAP bmph;
    uint32_t i, len, *dwords = data;
    ULONG runlength, index;

    // flip bits
    for (i = 0; i < Vcb->superblock.sector_size / sizeof(uint32_t); i++) {
        dwords[i] = ~dwords[i];
    }

    len = Vcb->superblock.sector_size * 8;

    RtlInitializeBitMap(&bmph, data, len);

    index = 0;
    runlength = RtlFindFirstRunClear(&bmph, &index);

    while (runlength != 0) {
        uint64_t addr, length;

        if (index >= len)
            break;

        if (index + runlength >= len) {
            runlength = len - index;

            if (runlength == 0)
                break;
        }

        addr = offset + (index * Vcb->superblock.sector_size);
        length = Vcb->superblock.sector_size * runlength;

        add_space_entry(&c->space, &c->space_size, addr, length);
        index += runlength;
        *total_space += length;

        runlength = RtlFindNextForwardRunClear(&bmph, index, &index);
    }
}