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
struct usbnet {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int ENOLINK ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int STATUS_CONN_OTHER ; 
 int nc_register_read (struct usbnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int net1080_check_connect(struct usbnet *dev)
{
	int			retval;
	u16			status;
	u16			vp;

	retval = nc_register_read(dev, REG_STATUS, &vp);
	status = vp;
	if (retval != 0) {
		netdev_dbg(dev->net, "net1080_check_conn read - %d\n", retval);
		return retval;
	}
	if ((status & STATUS_CONN_OTHER) != STATUS_CONN_OTHER)
		return -ENOLINK;
	return 0;
}