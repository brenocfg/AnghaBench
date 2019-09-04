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
typedef  int u16 ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 int EL2NSYNC ; 
 int /*<<< orphan*/  UDC_SOF ; 
 int UDC_TS ; 
 int UDC_TS_OK ; 
 int omap_readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_get_frame(struct usb_gadget *gadget)
{
	u16	sof = omap_readw(UDC_SOF);
	return (sof & UDC_TS_OK) ? (sof & UDC_TS) : -EL2NSYNC;
}