#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u64 ;
struct nvdimm_bus {int /*<<< orphan*/  badrange; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  badrange_forget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvdimm_clear_badblocks_regions (struct nvdimm_bus*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nvdimm_account_cleared_poison(struct nvdimm_bus *nvdimm_bus,
		phys_addr_t phys, u64 cleared)
{
	if (cleared > 0)
		badrange_forget(&nvdimm_bus->badrange, phys, cleared);

	if (cleared > 0 && cleared / 512)
		nvdimm_clear_badblocks_regions(nvdimm_bus, phys, cleared);
}