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
typedef  int u8 ;
struct Scsi_Host {int /*<<< orphan*/  io_port; } ;

/* Variables and functions */
 int CMD_BUSOFF_TIME ; 
 int CMD_BUSON_TIME ; 
 int CMD_DMASPEED ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  aha1542_intr_reset (int /*<<< orphan*/ ) ; 
 scalar_t__ aha1542_out (int /*<<< orphan*/ ,int*,int) ; 
 int clamp (int,int,int) ; 
 int dma_speed_hw (int) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 

__attribute__((used)) static void aha1542_set_bus_times(struct Scsi_Host *sh, int bus_on, int bus_off, int dma_speed)
{
	if (bus_on > 0) {
		u8 oncmd[] = { CMD_BUSON_TIME, clamp(bus_on, 2, 15) };

		aha1542_intr_reset(sh->io_port);
		if (aha1542_out(sh->io_port, oncmd, 2))
			goto fail;
	}

	if (bus_off > 0) {
		u8 offcmd[] = { CMD_BUSOFF_TIME, clamp(bus_off, 1, 64) };

		aha1542_intr_reset(sh->io_port);
		if (aha1542_out(sh->io_port, offcmd, 2))
			goto fail;
	}

	if (dma_speed_hw(dma_speed) != 0xff) {
		u8 dmacmd[] = { CMD_DMASPEED, dma_speed_hw(dma_speed) };

		aha1542_intr_reset(sh->io_port);
		if (aha1542_out(sh->io_port, dmacmd, 2))
			goto fail;
	}
	aha1542_intr_reset(sh->io_port);
	return;
fail:
	shost_printk(KERN_ERR, sh, "setting bus on/off-time failed\n");
	aha1542_intr_reset(sh->io_port);
}