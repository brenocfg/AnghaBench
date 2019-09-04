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
typedef  int u16 ;
struct ssb_pcicore {TYPE_1__* dev; } ;
struct TYPE_2__ {int core_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_PCICORE_SPROM (int /*<<< orphan*/ ) ; 
 int pcicore_read16 (struct ssb_pcicore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcicore_write16 (struct ssb_pcicore*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ssb_pcicore_fix_sprom_core_index(struct ssb_pcicore *pc)
{
	u16 tmp = pcicore_read16(pc, SSB_PCICORE_SPROM(0));
	if (((tmp & 0xF000) >> 12) != pc->dev->core_index) {
		tmp &= ~0xF000;
		tmp |= (pc->dev->core_index << 12);
		pcicore_write16(pc, SSB_PCICORE_SPROM(0), tmp);
	}
}