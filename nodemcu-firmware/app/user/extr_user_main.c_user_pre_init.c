#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  TYPE_1__ partition_item_t ;
typedef  enum flash_size_map { ____Placeholder_flash_size_map } flash_size_map ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_RCR_PHY_DATA ; 
 int /*<<< orphan*/  PLATFORM_RCR_PT ; 
 int SIZE_1024K ; 
 char SIZE_256K ; 
 int first_time_setup (TYPE_1__*,int,int) ; 
 TYPE_1__* os_malloc_iram (int) ; 
 int /*<<< orphan*/  os_memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  os_printf (char*,...) ; 
 int /*<<< orphan*/  phy_data_setup (TYPE_1__*,int) ; 
 int platform_rcr_read (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  rtctime_early_startup () ; 
 int system_get_flash_size_map () ; 
 scalar_t__ system_partition_table_regist (TYPE_1__*,int,int) ; 

void user_pre_init(void) {
#ifdef LUA_USE_MODULES_RTCTIME
  // Note: Keep this as close to call_user_start() as possible, since it
  // is where the cpu clock actually gets bumped to 80MHz.
    rtctime_early_startup ();
#endif
    partition_item_t *rcr_pt = NULL, *pt;
    enum flash_size_map fs_size_code = system_get_flash_size_map();
// Flash size lookup is SIZE_256K*2^N where N is as follows (see SDK/user_interface.h)
                                     /*   0   1   2   3   4   5   6   7   8   9  */
                                     /*  ½M  ¼M  1M  2M  4M  2M  4M  4M  8M 16M  */
    static char flash_size_scaler[] = "\001\000\002\003\004\003\004\004\005\006";
    uint32_t flash_size = SIZE_256K << flash_size_scaler[fs_size_code];

    uint32_t i = platform_rcr_read(PLATFORM_RCR_PT, (void **) &rcr_pt);
    uint32_t n = i / sizeof(partition_item_t);

    if (flash_size < SIZE_1024K) {
        os_printf("Flash size (%u) too small to support NodeMCU\n", flash_size);
        return;
    } else {
        os_printf("system SPI FI size:%u, Flash size: %u\n", fs_size_code, flash_size );
    }

    pt = os_malloc_iram(i);  // We will work on and register a copy of the PT in iRAM
    // Return if anything is amiss; The SDK will halt if the PT hasn't been registered
    if ( !rcr_pt || !pt || n * sizeof(partition_item_t) != i) {
        return;
    }
    os_memcpy(pt, rcr_pt, i);

    if (pt[n-1].type == 0) {
        // If the last PT entry is a {0,XX,0} end marker, then we need first time setup
        n = first_time_setup(pt, n-1, flash_size); // return n because setup might shrink the PT
    }

    if (platform_rcr_read(PLATFORM_RCR_PHY_DATA, NULL)!=0) {
        phy_data_setup(pt, n);
    }

    // Now register the partition and return
// for (i=0;i<n;i++) os_printf("P%d: %3d %06x %06x\n", i, pt[i].type, pt[i].addr, pt[i].size);
    if( fs_size_code > 1 && system_partition_table_regist(pt, n, fs_size_code)) {
        return;
    }
    os_printf("Invalid system partition table\n");
    while (1) {};  
}