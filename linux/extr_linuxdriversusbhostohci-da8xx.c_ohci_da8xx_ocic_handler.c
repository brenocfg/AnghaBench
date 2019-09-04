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
struct da8xx_ohci_root_hub {scalar_t__ (* get_oci ) (unsigned int) ;int /*<<< orphan*/  (* set_power ) (unsigned int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ocic_mask ; 
 scalar_t__ stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ohci_da8xx_ocic_handler(struct da8xx_ohci_root_hub *hub,
				    unsigned port)
{
	ocic_mask |= 1 << port;

	/* Once over-current is detected, the port needs to be powered down */
	if (hub->get_oci(port) > 0)
		hub->set_power(port, 0);
}