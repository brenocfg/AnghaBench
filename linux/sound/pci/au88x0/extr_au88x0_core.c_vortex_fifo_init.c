#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  mmio; TYPE_1__* card; } ;
typedef  TYPE_2__ vortex_t ;
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_SIZE ; 
 int FIFO_U0 ; 
 int FIFO_U1 ; 
 int NR_ADB ; 
 int NR_WT ; 
 int VORTEX_FIFO_ADBCTRL ; 
 int VORTEX_FIFO_WTCTRL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int hwread (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hwwrite (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vortex_fifo_clearadbdata (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_fifo_clearwtdata (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_fifo_init(vortex_t * vortex)
{
	int x;
	u32 addr;

	/* ADB DMA channels fifos. */
	addr = VORTEX_FIFO_ADBCTRL + ((NR_ADB - 1) * 4);
	for (x = NR_ADB - 1; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, (FIFO_U0 | FIFO_U1));
		if (hwread(vortex->mmio, addr) != (FIFO_U0 | FIFO_U1))
			dev_err(vortex->card->dev, "bad adb fifo reset!\n");
		vortex_fifo_clearadbdata(vortex, x, FIFO_SIZE);
		addr -= 4;
	}

#ifndef CHIP_AU8810
	/* WT DMA channels fifos. */
	addr = VORTEX_FIFO_WTCTRL + ((NR_WT - 1) * 4);
	for (x = NR_WT - 1; x >= 0; x--) {
		hwwrite(vortex->mmio, addr, FIFO_U0);
		if (hwread(vortex->mmio, addr) != FIFO_U0)
			dev_err(vortex->card->dev,
				"bad wt fifo reset (0x%08x, 0x%08x)!\n",
				addr, hwread(vortex->mmio, addr));
		vortex_fifo_clearwtdata(vortex, x, FIFO_SIZE);
		addr -= 4;
	}
#endif
	/* trigger... */
#ifdef CHIP_AU8820
	hwwrite(vortex->mmio, 0xf8c0, 0xd03);	//0x0843 0xd6b
#else
#ifdef CHIP_AU8830
	hwwrite(vortex->mmio, 0x17000, 0x61);	/* wt a */
	hwwrite(vortex->mmio, 0x17004, 0x61);	/* wt b */
#endif
	hwwrite(vortex->mmio, 0x17008, 0x61);	/* adb */
#endif
}