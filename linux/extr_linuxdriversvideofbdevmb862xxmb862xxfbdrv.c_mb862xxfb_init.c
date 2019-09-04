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

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int mb862xxfb_init(void)
{
	int ret = -ENODEV;

#if defined(CONFIG_FB_MB862XX_LIME)
	ret = platform_driver_register(&of_platform_mb862xxfb_driver);
#endif
#if defined(CONFIG_FB_MB862XX_PCI_GDC)
	ret = pci_register_driver(&mb862xxfb_pci_driver);
#endif
	return ret;
}