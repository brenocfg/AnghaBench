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
typedef  int u32 ;
struct sata_oxnas_host_priv {scalar_t__ core_base; } ;
struct ata_host {struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 scalar_t__ DEVICE_CONTROL ; 
 int DEVICE_CONTROL_ATA_ERR_OVERRIDE ; 
 int /*<<< orphan*/  DPRINTK (char*) ; 
 int /*<<< orphan*/  OXNASSATA_NOTRAID ; 
 scalar_t__ PORT_ERROR_MASK ; 
 int /*<<< orphan*/  UNKNOWN_MODE ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  sata_oxnas_set_mode (struct ata_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void sata_oxnas_reset_ucode(struct ata_host *ah, int force,
					  int no_microcode)
{
	struct sata_oxnas_host_priv *hd = ah->private_data;

	DPRINTK("ENTER\n");
	if (no_microcode) {
		u32 reg;

		sata_oxnas_set_mode(ah, UNKNOWN_MODE, force);
		reg = ioread32(hd->core_base + DEVICE_CONTROL);
		reg |= DEVICE_CONTROL_ATA_ERR_OVERRIDE;
		iowrite32(reg, hd->core_base + DEVICE_CONTROL);
	} else {
		/* JBOD uCode */
		sata_oxnas_set_mode(ah, OXNASSATA_NOTRAID, force);
		/* Turn the work around off as it may have been left on by any
		 * HW-RAID code that we've been working with */
		iowrite32(0x0, hd->core_base + PORT_ERROR_MASK);
	}
}