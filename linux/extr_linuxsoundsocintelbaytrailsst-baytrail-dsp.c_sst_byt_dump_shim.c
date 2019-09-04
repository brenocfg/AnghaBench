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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ pci_cfg; } ;
struct sst_dsp {int /*<<< orphan*/  dev; TYPE_1__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,scalar_t__) ; 
 scalar_t__ readl (scalar_t__) ; 
 scalar_t__ sst_dsp_shim_read64_unlocked (struct sst_dsp*,int) ; 

__attribute__((used)) static void sst_byt_dump_shim(struct sst_dsp *sst)
{
	int i;
	u64 reg;

	for (i = 0; i <= 0xF0; i += 8) {
		reg = sst_dsp_shim_read64_unlocked(sst, i);
		if (reg)
			dev_dbg(sst->dev, "shim 0x%2.2x value 0x%16.16llx\n",
				i, reg);
	}

	for (i = 0x00; i <= 0xff; i += 4) {
		reg = readl(sst->addr.pci_cfg + i);
		if (reg)
			dev_dbg(sst->dev, "pci 0x%2.2x value 0x%8.8x\n",
				i, (u32)reg);
	}
}