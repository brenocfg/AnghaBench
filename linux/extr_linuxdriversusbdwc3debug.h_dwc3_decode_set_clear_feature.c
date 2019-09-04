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
typedef  int const __u16 ;

/* Variables and functions */
#define  TEST_FORCE_EN 141 
#define  TEST_J 140 
#define  TEST_K 139 
#define  TEST_PACKET 138 
#define  TEST_SE0_NAK 137 
#define  USB_DEVICE_LTM_ENABLE 136 
#define  USB_DEVICE_REMOTE_WAKEUP 135 
#define  USB_DEVICE_SELF_POWERED 134 
#define  USB_DEVICE_TEST_MODE 133 
#define  USB_DEVICE_U1_ENABLE 132 
#define  USB_DEVICE_U2_ENABLE 131 
 int const USB_DIR_IN ; 
 int const USB_ENDPOINT_HALT ; 
 int const USB_INTRF_FUNC_SUSPEND ; 
#define  USB_RECIP_DEVICE 130 
#define  USB_RECIP_ENDPOINT 129 
#define  USB_RECIP_INTERFACE 128 
 int USB_RECIP_MASK ; 
 int USB_REQ_CLEAR_FEATURE ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,...) ; 

__attribute__((used)) static inline void dwc3_decode_set_clear_feature(__u8 t, __u8 b, __u16 v,
						 __u16 i, char *str)
{
	switch (t & USB_RECIP_MASK) {
	case USB_RECIP_DEVICE:
		sprintf(str, "%s Device Feature(%s%s)",
			b == USB_REQ_CLEAR_FEATURE ? "Clear" : "Set",
			({char *s;
				switch (v) {
				case USB_DEVICE_SELF_POWERED:
					s = "Self Powered";
					break;
				case USB_DEVICE_REMOTE_WAKEUP:
					s = "Remote Wakeup";
					break;
				case USB_DEVICE_TEST_MODE:
					s = "Test Mode";
					break;
				case USB_DEVICE_U1_ENABLE:
					s = "U1 Enable";
					break;
				case USB_DEVICE_U2_ENABLE:
					s = "U2 Enable";
					break;
				case USB_DEVICE_LTM_ENABLE:
					s = "LTM Enable";
					break;
				default:
					s = "UNKNOWN";
				} s; }),
			v == USB_DEVICE_TEST_MODE ?
			({ char *s;
				switch (i) {
				case TEST_J:
					s = ": TEST_J";
					break;
				case TEST_K:
					s = ": TEST_K";
					break;
				case TEST_SE0_NAK:
					s = ": TEST_SE0_NAK";
					break;
				case TEST_PACKET:
					s = ": TEST_PACKET";
					break;
				case TEST_FORCE_EN:
					s = ": TEST_FORCE_EN";
					break;
				default:
					s = ": UNKNOWN";
				} s; }) : "");
		break;
	case USB_RECIP_INTERFACE:
		sprintf(str, "%s Interface Feature(%s)",
			b == USB_REQ_CLEAR_FEATURE ? "Clear" : "Set",
			v == USB_INTRF_FUNC_SUSPEND ?
			"Function Suspend" : "UNKNOWN");
		break;
	case USB_RECIP_ENDPOINT:
		sprintf(str, "%s Endpoint Feature(%s ep%d%s)",
			b == USB_REQ_CLEAR_FEATURE ? "Clear" : "Set",
			v == USB_ENDPOINT_HALT ? "Halt" : "UNKNOWN",
			i & ~USB_DIR_IN,
			i & USB_DIR_IN ? "in" : "out");
		break;
	}
}