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
typedef  int u32 ;
struct ssb_chipcommon {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_CHIPCO_FLASHCTL ; 
 int SSB_CHIPCO_FLASHCTL_BUSY ; 
 int SSB_CHIPCO_FLASHCTL_START ; 
 int chipco_read32 (struct ssb_chipcommon*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipco_write32 (struct ssb_chipcommon*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ssb_sflash_cmd(struct ssb_chipcommon *cc, u32 opcode)
{
	int i;
	chipco_write32(cc, SSB_CHIPCO_FLASHCTL,
		       SSB_CHIPCO_FLASHCTL_START | opcode);
	for (i = 0; i < 1000; i++) {
		if (!(chipco_read32(cc, SSB_CHIPCO_FLASHCTL) &
		      SSB_CHIPCO_FLASHCTL_BUSY))
			return;
		cpu_relax();
	}
	dev_err(cc->dev->dev, "SFLASH control command failed (timeout)!\n");
}