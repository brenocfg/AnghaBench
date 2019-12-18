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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  superblock ;
struct TYPE_4__ {int /*<<< orphan*/  sector_size; } ;
struct TYPE_5__ {TYPE_1__ superblock; } ;
typedef  TYPE_2__ device_extension ;
typedef  int /*<<< orphan*/  device ;
typedef  scalar_t__ ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  add_trim_entry (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sector_align (int,int /*<<< orphan*/ ) ; 
 scalar_t__* superblock_addrs ; 

void add_trim_entry_avoid_sb(device_extension* Vcb, device* dev, uint64_t address, uint64_t size) {
    int i;
    ULONG sblen = (ULONG)sector_align(sizeof(superblock), Vcb->superblock.sector_size);

    i = 0;
    while (superblock_addrs[i] != 0) {
        if (superblock_addrs[i] + sblen >= address && superblock_addrs[i] < address + size) {
            if (superblock_addrs[i] > address)
                add_trim_entry(dev, address, superblock_addrs[i] - address);

            if (size <= superblock_addrs[i] + sblen - address)
                return;

            size -= superblock_addrs[i] + sblen - address;
            address = superblock_addrs[i] + sblen;
        } else if (superblock_addrs[i] > address + size)
            break;

        i++;
    }

    add_trim_entry(dev, address, size);
}