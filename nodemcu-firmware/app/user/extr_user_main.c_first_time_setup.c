#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int type; int size; int addr; } ;
typedef  TYPE_1__ partition_item_t ;

/* Variables and functions */
 int INTERNAL_FLASH_SECTOR_SIZE ; 
 int IROM0_SIZE ; 
#define  NODEMCU_PARTITION_IROM0TEXT 130 
#define  NODEMCU_PARTITION_LFS 129 
#define  NODEMCU_PARTITION_SPIFFS 128 
 int /*<<< orphan*/  PLATFORM_RCR_PT ; 
 void* PT_ALIGN (int) ; 
 int /*<<< orphan*/  _ResetHandler () ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int /*<<< orphan*/  os_printf (char*,int) ; 
 int /*<<< orphan*/  platform_rcr_write (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static uint32_t first_time_setup(partition_item_t *pt, uint32_t n, uint32_t flash_size) {
    int i, j, last = 0, newn = n;
    /*
    * Scan down the PT adjusting and 0 entries to sensible defaults.  Also delete any
    * zero-sized partitions (as the SDK barfs on these).
    */
    for (i = 0, j = 0; i < n; i ++) {
        partition_item_t *p = pt + i;
        switch (p->type) {

          case NODEMCU_PARTITION_IROM0TEXT:
            // If the IROM0 partition size is 0 then compute from the IROM0_SIZE. Note
            // that the size in the end-marker is used by the nodemcu-partition.py
            // script and not here.
            if (p->size == 0) {
                p->size = PT_ALIGN(IROM0_SIZE);
            }
            break;

          case NODEMCU_PARTITION_LFS:
            // Properly align the LFS partition size and make it consecutive to
            // the previous partition.
            p->size = PT_ALIGN(p->size);
            if (p->addr == 0)
                p->addr = last;
            break;

          case NODEMCU_PARTITION_SPIFFS:
            if (p->size == ~0x0 && p->addr == 0) {
                // This allocate all the remaining flash to SPIFFS
                p->addr = last;
                p->size = flash_size - last;
            } else if (p->size == ~0x0) {
                p->size = flash_size - p->addr;
           }  else if (p->addr == 0) {
                // if the is addr not specified then start SPIFFS at 1Mb
                // boundary if the size will fit otherwise make it consecutive
                // to the previous partition.
                p->addr = (p->size <= flash_size - 0x100000) ? 0x100000 : last;
            }
        }

        if (p->size == 0) {
            // Delete 0-sized partitions as the SDK barfs on these
            newn--;
        } else {
            // Do consistency tests on the partition
            if (p->addr & (INTERNAL_FLASH_SECTOR_SIZE - 1) ||
                p->size & (INTERNAL_FLASH_SECTOR_SIZE - 1) ||
                p->addr < last ||
                p->addr + p->size > flash_size) {
                os_printf("Partition %u invalid alignment\n", i);
                while(1) {/*system_soft_wdt_feed ();*/}
            }
            if (j < i)   // shift the partition down if we have any deleted slots
                pt[j] = *p;
//os_printf("Partition %d: %04x %06x %06x\n", j, p->type, p->addr, p->size);
            j++;
            last = p->addr + p->size;
        }
    }

    platform_rcr_write(PLATFORM_RCR_PT, pt, newn*sizeof(partition_item_t));
    ets_delay_us(5000);
    _ResetHandler(); // Trigger reset; the new PT will be loaded on reboot
}