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
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vrc4171_card_device ; 
 int /*<<< orphan*/  vrc4171_card_driver ; 
 int /*<<< orphan*/  vrc4171_irq ; 
 int /*<<< orphan*/  vrc4171_remove_sockets () ; 
 int /*<<< orphan*/  vrc4171_sockets ; 

__attribute__((used)) static void vrc4171_card_exit(void)
{
	free_irq(vrc4171_irq, vrc4171_sockets);
	vrc4171_remove_sockets();
	platform_device_unregister(&vrc4171_card_device);
	platform_driver_unregister(&vrc4171_card_driver);
}