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
struct nbu2ss_udc {int /*<<< orphan*/  remote_wakeup; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int MAX_TEST_MODE_NUM ; 
 int /*<<< orphan*/  U2F_ENABLE ; 
#define  USB_DEVICE_REMOTE_WAKEUP 129 
#define  USB_DEVICE_TEST_MODE 128 

__attribute__((used)) static int _nbu2ss_set_feature_device(
	struct nbu2ss_udc *udc,
	u16 selector,
	u16 wIndex
)
{
	int	result = -EOPNOTSUPP;

	switch (selector) {
	case USB_DEVICE_REMOTE_WAKEUP:
		if (wIndex == 0x0000) {
			udc->remote_wakeup = U2F_ENABLE;
			result = 0;
		}
		break;

	case USB_DEVICE_TEST_MODE:
		wIndex >>= 8;
		if (wIndex <= MAX_TEST_MODE_NUM)
			result = 0;
		break;

	default:
		break;
	}

	return result;
}