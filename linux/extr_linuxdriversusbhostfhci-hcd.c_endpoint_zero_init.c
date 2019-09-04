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
typedef  scalar_t__ u32 ;
struct fhci_usb {int /*<<< orphan*/  ep0; } ;
typedef  enum fhci_mem_alloc { ____Placeholder_fhci_mem_alloc } fhci_mem_alloc ;

/* Variables and functions */
 scalar_t__ fhci_create_ep (struct fhci_usb*,int,scalar_t__) ; 
 int /*<<< orphan*/  fhci_init_ep_registers (struct fhci_usb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 endpoint_zero_init(struct fhci_usb *usb,
			      enum fhci_mem_alloc data_mem,
			      u32 ring_len)
{
	u32 rc;

	rc = fhci_create_ep(usb, data_mem, ring_len);
	if (rc)
		return rc;

	/* inilialize endpoint registers */
	fhci_init_ep_registers(usb, usb->ep0, data_mem);

	return 0;
}