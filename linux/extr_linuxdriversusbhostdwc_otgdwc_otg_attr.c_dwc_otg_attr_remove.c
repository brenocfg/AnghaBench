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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 TYPE_1__* dev ; 
 int /*<<< orphan*/  dev_attr_busconnected ; 
 int /*<<< orphan*/  dev_attr_buspower ; 
 int /*<<< orphan*/  dev_attr_bussuspend ; 
 int /*<<< orphan*/  dev_attr_devspeed ; 
 int /*<<< orphan*/  dev_attr_disconnect_us ; 
 int /*<<< orphan*/  dev_attr_enumspeed ; 
 int /*<<< orphan*/  dev_attr_fr_interval ; 
 int /*<<< orphan*/  dev_attr_ggpio ; 
 int /*<<< orphan*/  dev_attr_gnptxfsiz ; 
 int /*<<< orphan*/  dev_attr_gotgctl ; 
 int /*<<< orphan*/  dev_attr_gpvndctl ; 
 int /*<<< orphan*/  dev_attr_grxfsiz ; 
 int /*<<< orphan*/  dev_attr_gsnpsid ; 
 int /*<<< orphan*/  dev_attr_guid ; 
 int /*<<< orphan*/  dev_attr_gusbcfg ; 
 int /*<<< orphan*/  dev_attr_hcd_frrem ; 
 int /*<<< orphan*/  dev_attr_hcddump ; 
 int /*<<< orphan*/  dev_attr_hnp ; 
 int /*<<< orphan*/  dev_attr_hnpcapable ; 
 int /*<<< orphan*/  dev_attr_hprt0 ; 
 int /*<<< orphan*/  dev_attr_hptxfsiz ; 
 int /*<<< orphan*/  dev_attr_hsic_connect ; 
 int /*<<< orphan*/  dev_attr_inv_sel_hsic ; 
 int /*<<< orphan*/  dev_attr_mode ; 
 int /*<<< orphan*/  dev_attr_mode_ch_tim_en ; 
 int /*<<< orphan*/  dev_attr_rd_reg_test ; 
 int /*<<< orphan*/  dev_attr_regdump ; 
 int /*<<< orphan*/  dev_attr_regoffset ; 
 int /*<<< orphan*/  dev_attr_regvalue ; 
 int /*<<< orphan*/  dev_attr_rem_wakeup_pwrdn ; 
 int /*<<< orphan*/  dev_attr_remote_wakeup ; 
 int /*<<< orphan*/  dev_attr_spramdump ; 
 int /*<<< orphan*/  dev_attr_srp ; 
 int /*<<< orphan*/  dev_attr_srpcapable ; 
 int /*<<< orphan*/  dev_attr_wr_reg_test ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dwc_otg_attr_remove(
#ifdef LM_INTERFACE
	struct lm_device *dev
#elif  defined(PCI_INTERFACE)
	struct pci_dev *dev
#elif  defined(PLATFORM_INTERFACE)
	struct platform_device *dev
#endif
    )
{
	device_remove_file(&dev->dev, &dev_attr_regoffset);
	device_remove_file(&dev->dev, &dev_attr_regvalue);
	device_remove_file(&dev->dev, &dev_attr_mode);
	device_remove_file(&dev->dev, &dev_attr_hnpcapable);
	device_remove_file(&dev->dev, &dev_attr_srpcapable);
	device_remove_file(&dev->dev, &dev_attr_hsic_connect);
	device_remove_file(&dev->dev, &dev_attr_inv_sel_hsic);
	device_remove_file(&dev->dev, &dev_attr_hnp);
	device_remove_file(&dev->dev, &dev_attr_srp);
	device_remove_file(&dev->dev, &dev_attr_buspower);
	device_remove_file(&dev->dev, &dev_attr_bussuspend);
	device_remove_file(&dev->dev, &dev_attr_mode_ch_tim_en);
	device_remove_file(&dev->dev, &dev_attr_fr_interval);
	device_remove_file(&dev->dev, &dev_attr_busconnected);
	device_remove_file(&dev->dev, &dev_attr_gotgctl);
	device_remove_file(&dev->dev, &dev_attr_gusbcfg);
	device_remove_file(&dev->dev, &dev_attr_grxfsiz);
	device_remove_file(&dev->dev, &dev_attr_gnptxfsiz);
	device_remove_file(&dev->dev, &dev_attr_gpvndctl);
	device_remove_file(&dev->dev, &dev_attr_ggpio);
	device_remove_file(&dev->dev, &dev_attr_guid);
	device_remove_file(&dev->dev, &dev_attr_gsnpsid);
	device_remove_file(&dev->dev, &dev_attr_devspeed);
	device_remove_file(&dev->dev, &dev_attr_enumspeed);
	device_remove_file(&dev->dev, &dev_attr_hptxfsiz);
	device_remove_file(&dev->dev, &dev_attr_hprt0);
	device_remove_file(&dev->dev, &dev_attr_remote_wakeup);
	device_remove_file(&dev->dev, &dev_attr_rem_wakeup_pwrdn);
	device_remove_file(&dev->dev, &dev_attr_disconnect_us);
	device_remove_file(&dev->dev, &dev_attr_regdump);
	device_remove_file(&dev->dev, &dev_attr_spramdump);
	device_remove_file(&dev->dev, &dev_attr_hcddump);
	device_remove_file(&dev->dev, &dev_attr_hcd_frrem);
	device_remove_file(&dev->dev, &dev_attr_rd_reg_test);
	device_remove_file(&dev->dev, &dev_attr_wr_reg_test);
#ifdef CONFIG_USB_DWC_OTG_LPM
	device_remove_file(&dev->dev, &dev_attr_lpm_response);
	device_remove_file(&dev->dev, &dev_attr_sleep_status);
#endif
}