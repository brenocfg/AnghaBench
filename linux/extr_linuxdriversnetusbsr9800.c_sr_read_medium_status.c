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
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  SR_CMD_READ_MEDIUM_STATUS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sr_read_cmd (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 sr_read_medium_status(struct usbnet *dev)
{
	__le16 v;
	int ret;

	ret = sr_read_cmd(dev, SR_CMD_READ_MEDIUM_STATUS, 0, 0, 2, &v);
	if (ret < 0) {
		netdev_err(dev->net,
			   "Error reading Medium Status register:%02x\n", ret);
		return ret;	/* TODO: callers not checking for error ret */
	}

	return le16_to_cpu(v);
}