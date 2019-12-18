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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ base_address; int sector_count; int sector_size; } ;

/* Variables and functions */
 int MP_ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* flash_layout ; 

__attribute__((used)) static uint32_t flash_get_sector_index(uint32_t addr, uint32_t *sector_size) {
    if (addr >= flash_layout[0].base_address) {
        uint32_t sector_index = 0;
        for (int i = 0; i < MP_ARRAY_SIZE(flash_layout); ++i) {
            for (int j = 0; j < flash_layout[i].sector_count; ++j) {
                uint32_t sector_start_next = flash_layout[i].base_address
                    + (j + 1) * flash_layout[i].sector_size;
                if (addr < sector_start_next) {
                    *sector_size = flash_layout[i].sector_size;
                    return sector_index;
                }
                ++sector_index;
            }
        }
    }
    return 0;
}