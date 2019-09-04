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
 int /*<<< orphan*/  i810fb_driver ; 
 int /*<<< orphan*/  i810fb_setup (char*) ; 
 int pci_register_driver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i810fb_init(void)
{
	char *option = NULL;

	if (fb_get_options("i810fb", &option))
		return -ENODEV;
	i810fb_setup(option);

	return pci_register_driver(&i810fb_driver);
}