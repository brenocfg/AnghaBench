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
 scalar_t__ fb_get_options (char*,char**) ; 
 int pci_register_driver (int /*<<< orphan*/ *) ; 
 int tc_register_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tgafb_pci_driver ; 
 int /*<<< orphan*/  tgafb_setup (char*) ; 
 int /*<<< orphan*/  tgafb_tc_driver ; 

__attribute__((used)) static int tgafb_init(void)
{
	int status;
#ifndef MODULE
	char *option = NULL;

	if (fb_get_options("tgafb", &option))
		return -ENODEV;
	tgafb_setup(option);
#endif
	status = pci_register_driver(&tgafb_pci_driver);
	if (!status)
		status = tc_register_driver(&tgafb_tc_driver);
	return status;
}