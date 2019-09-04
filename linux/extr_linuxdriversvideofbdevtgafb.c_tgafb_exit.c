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
 int /*<<< orphan*/  pci_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tc_unregister_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tgafb_pci_driver ; 
 int /*<<< orphan*/  tgafb_tc_driver ; 

__attribute__((used)) static void tgafb_exit(void)
{
	tc_unregister_driver(&tgafb_tc_driver);
	pci_unregister_driver(&tgafb_pci_driver);
}