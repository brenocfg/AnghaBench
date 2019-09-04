#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usblp {char* device_id_string; int /*<<< orphan*/  minor; TYPE_1__* intf; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int USBLP_DEVICE_ID_SIZE ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,...) ; 
 int usblp_get_id (struct usblp*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int usblp_cache_device_id_string(struct usblp *usblp)
{
	int err, length;

	err = usblp_get_id(usblp, 0, usblp->device_id_string, USBLP_DEVICE_ID_SIZE - 1);
	if (err < 0) {
		dev_dbg(&usblp->intf->dev,
			"usblp%d: error = %d reading IEEE-1284 Device ID string\n",
			usblp->minor, err);
		usblp->device_id_string[0] = usblp->device_id_string[1] = '\0';
		return -EIO;
	}

	/* First two bytes are length in big-endian.
	 * They count themselves, and we copy them into
	 * the user's buffer. */
	length = be16_to_cpu(*((__be16 *)usblp->device_id_string));
	if (length < 2)
		length = 2;
	else if (length >= USBLP_DEVICE_ID_SIZE)
		length = USBLP_DEVICE_ID_SIZE - 1;
	usblp->device_id_string[length] = '\0';

	dev_dbg(&usblp->intf->dev, "usblp%d Device ID string [len=%d]=\"%s\"\n",
		usblp->minor, length, &usblp->device_id_string[2]);

	return length;
}