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
struct platform_device {int dummy; } ;
struct cpcap_phy_ddata {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cpcap_phy_irqs ; 
 int cpcap_usb_init_irq (struct platform_device*,struct cpcap_phy_ddata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cpcap_usb_init_interrupts(struct platform_device *pdev,
				     struct cpcap_phy_ddata *ddata)
{
	int i, error;

	for (i = 0; i < ARRAY_SIZE(cpcap_phy_irqs); i++) {
		error = cpcap_usb_init_irq(pdev, ddata, cpcap_phy_irqs[i]);
		if (error)
			return error;
	}

	return 0;
}