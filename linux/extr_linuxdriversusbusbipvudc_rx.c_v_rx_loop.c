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
struct usbip_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 scalar_t__ usbip_event_happened (struct usbip_device*) ; 
 int v_rx_pdu (struct usbip_device*) ; 

int v_rx_loop(void *data)
{
	struct usbip_device *ud = data;
	int ret = 0;

	while (!kthread_should_stop()) {
		if (usbip_event_happened(ud))
			break;
		ret = v_rx_pdu(ud);
		if (ret < 0) {
			pr_warn("v_rx exit with error %d", ret);
			break;
		}
	}
	return ret;
}