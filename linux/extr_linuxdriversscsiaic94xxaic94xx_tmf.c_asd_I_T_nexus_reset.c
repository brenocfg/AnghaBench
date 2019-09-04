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
struct sas_phy {int /*<<< orphan*/  dev; } ;
struct domain_device {scalar_t__ dev_type; int tproto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NEXUS_PHASE_POST ; 
 int /*<<< orphan*/  NEXUS_PHASE_PRE ; 
 int /*<<< orphan*/  NEXUS_PHASE_RESUME ; 
 int SAS_PROTOCOL_STP ; 
 scalar_t__ SAS_SATA_DEV ; 
 int TC_RESUME ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 int asd_clear_nexus_I_T (struct domain_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct sas_phy* sas_get_local_phy (struct domain_device*) ; 
 int sas_phy_reset (struct sas_phy*,int) ; 
 int /*<<< orphan*/  sas_put_local_phy (struct sas_phy*) ; 

int asd_I_T_nexus_reset(struct domain_device *dev)
{
	int res, tmp_res, i;
	struct sas_phy *phy = sas_get_local_phy(dev);
	/* Standard mandates link reset for ATA  (type 0) and
	 * hard reset for SSP (type 1) */
	int reset_type = (dev->dev_type == SAS_SATA_DEV ||
			  (dev->tproto & SAS_PROTOCOL_STP)) ? 0 : 1;

	asd_clear_nexus_I_T(dev, NEXUS_PHASE_PRE);
	/* send a hard reset */
	ASD_DPRINTK("sending %s reset to %s\n",
		    reset_type ? "hard" : "soft", dev_name(&phy->dev));
	res = sas_phy_reset(phy, reset_type);
	if (res == TMF_RESP_FUNC_COMPLETE || res == -ENODEV) {
		/* wait for the maximum settle time */
		msleep(500);
		/* clear all outstanding commands (keep nexus suspended) */
		asd_clear_nexus_I_T(dev, NEXUS_PHASE_POST);
	}
	for (i = 0 ; i < 3; i++) {
		tmp_res = asd_clear_nexus_I_T(dev, NEXUS_PHASE_RESUME);
		if (tmp_res == TC_RESUME)
			goto out;
		msleep(500);
	}

	/* This is a bit of a problem:  the sequencer is still suspended
	 * and is refusing to resume.  Hope it will resume on a bigger hammer
	 * or the disk is lost */
	dev_printk(KERN_ERR, &phy->dev,
		   "Failed to resume nexus after reset 0x%x\n", tmp_res);

	res = TMF_RESP_FUNC_FAILED;
 out:
	sas_put_local_phy(phy);
	return res;
}