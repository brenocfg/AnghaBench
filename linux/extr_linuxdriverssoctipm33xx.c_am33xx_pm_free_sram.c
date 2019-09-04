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
struct am33xx_pm_ro_sram_data {int dummy; } ;
struct TYPE_2__ {int* do_wfi_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocmcram_location ; 
 int /*<<< orphan*/  ocmcram_location_data ; 
 TYPE_1__* pm_sram ; 
 int /*<<< orphan*/  sram_pool ; 
 int /*<<< orphan*/  sram_pool_data ; 

__attribute__((used)) static void am33xx_pm_free_sram(void)
{
	gen_pool_free(sram_pool, ocmcram_location, *pm_sram->do_wfi_sz);
	gen_pool_free(sram_pool_data, ocmcram_location_data,
		      sizeof(struct am33xx_pm_ro_sram_data));
}