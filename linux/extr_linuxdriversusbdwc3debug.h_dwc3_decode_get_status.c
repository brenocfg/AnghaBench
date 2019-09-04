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
typedef  int __u8 ;
typedef  int __u16 ;

/* Variables and functions */
 int USB_DIR_IN ; 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static inline void dwc3_decode_get_status(__u8 t, __u16 i, __u16 l, char *str)
{
	switch (t & USB_RECIP_MASK) {
	case USB_RECIP_INTERFACE:
		sprintf(str, "Get Interface Status(Intf = %d, Length = %d)",
			i, l);
		break;
	case USB_RECIP_ENDPOINT:
		sprintf(str, "Get Endpoint Status(ep%d%s)",
			i & ~USB_DIR_IN,
			i & USB_DIR_IN ? "in" : "out");
		break;
	}
}