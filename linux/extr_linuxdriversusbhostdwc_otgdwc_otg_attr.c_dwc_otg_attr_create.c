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
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dwc_otg_attr_create(
#ifdef LM_INTERFACE
	struct lm_device *dev
#elif  defined(PCI_INTERFACE)
	struct pci_dev *dev
#elif  defined(PLATFORM_INTERFACE)
        struct platform_device *dev
#endif
    )
{
	int error;

	error = device_create_file(&dev->dev, &dev_attr_regoffset);
	error = device_create_file(&dev->dev, &dev_attr_regvalue);
	error = device_create_file(&dev->dev, &dev_attr_mode);
	error = device_create_file(&dev->dev, &dev_attr_hnpcapable);
	error = device_create_file(&dev->dev, &dev_attr_srpcapable);
	error = device_create_file(&dev->dev, &dev_attr_hsic_connect);
	error = device_create_file(&dev->dev, &dev_attr_inv_sel_hsic);
	error = device_create_file(&dev->dev, &dev_attr_hnp);
	error = device_create_file(&dev->dev, &dev_attr_srp);
	error = device_create_file(&dev->dev, &dev_attr_buspower);
	error = device_create_file(&dev->dev, &dev_attr_bussuspend);
	error = device_create_file(&dev->dev, &dev_attr_mode_ch_tim_en);
	error = device_create_file(&dev->dev, &dev_attr_fr_interval);
	error = device_create_file(&dev->dev, &dev_attr_busconnected);
	error = device_create_file(&dev->dev, &dev_attr_gotgctl);
	error = device_create_file(&dev->dev, &dev_attr_gusbcfg);
	error = device_create_file(&dev->dev, &dev_attr_grxfsiz);
	error = device_create_file(&dev->dev, &dev_attr_gnptxfsiz);
	error = device_create_file(&dev->dev, &dev_attr_gpvndctl);
	error = device_create_file(&dev->dev, &dev_attr_ggpio);
	error = device_create_file(&dev->dev, &dev_attr_guid);
	error = device_create_file(&dev->dev, &dev_attr_gsnpsid);
	error = device_create_file(&dev->dev, &dev_attr_devspeed);
	error = device_create_file(&dev->dev, &dev_attr_enumspeed);
	error = device_create_file(&dev->dev, &dev_attr_hptxfsiz);
	error = device_create_file(&dev->dev, &dev_attr_hprt0);
	error = device_create_file(&dev->dev, &dev_attr_remote_wakeup);
	error = device_create_file(&dev->dev, &dev_attr_rem_wakeup_pwrdn);
	error = device_create_file(&dev->dev, &dev_attr_disconnect_us);
	error = device_create_file(&dev->dev, &dev_attr_regdump);
	error = device_create_file(&dev->dev, &dev_attr_spramdump);
	error = device_create_file(&dev->dev, &dev_attr_hcddump);
	error = device_create_file(&dev->dev, &dev_attr_hcd_frrem);
	error = device_create_file(&dev->dev, &dev_attr_rd_reg_test);
	error = device_create_file(&dev->dev, &dev_attr_wr_reg_test);
#ifdef CONFIG_USB_DWC_OTG_LPM
	error = device_create_file(&dev->dev, &dev_attr_lpm_response);
	error = device_create_file(&dev->dev, &dev_attr_sleep_status);
#endif
}