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
typedef  int /*<<< orphan*/  u8 ;
struct zero_dev {int dummy; } ;
struct usb_request {unsigned int actual; int /*<<< orphan*/ * buf; } ;
struct usb_ep {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ERROR (struct zero_dev*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int pattern ; 
 int /*<<< orphan*/  usb_ep_set_halt (struct usb_ep*) ; 

__attribute__((used)) static int
check_read_data (
	struct zero_dev		*dev,
	struct usb_ep		*ep,
	struct usb_request	*req
)
{
	unsigned	i;
	u8		*buf = req->buf;

	for (i = 0; i < req->actual; i++, buf++) {
		switch (pattern) {
		/* all-zeroes has no synchronization issues */
		case 0:
			if (*buf == 0)
				continue;
			break;
		/* mod63 stays in sync with short-terminated transfers,
		 * or otherwise when host and gadget agree on how large
		 * each usb transfer request should be.  resync is done
		 * with set_interface or set_config.
		 */
		case 1:
			if (*buf == (u8)(i % 63))
				continue;
			break;
		}
		ERROR (dev, "bad OUT byte, buf [%d] = %d\n", i, *buf);
		usb_ep_set_halt (ep);
		return -EINVAL;
	}
	return 0;
}