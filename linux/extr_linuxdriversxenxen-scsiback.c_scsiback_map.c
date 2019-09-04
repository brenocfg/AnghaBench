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
struct xenbus_device {int /*<<< orphan*/  otherend; } ;
struct vscsibk_info {struct xenbus_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  XBT_NIL ; 
 int scsiback_init_sring (struct vscsibk_info*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*,int /*<<< orphan*/ ) ; 
 int xenbus_gather (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,unsigned int*,char*,char*,unsigned int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scsiback_map(struct vscsibk_info *info)
{
	struct xenbus_device *dev = info->dev;
	unsigned int ring_ref, evtchn;
	int err;

	err = xenbus_gather(XBT_NIL, dev->otherend,
			"ring-ref", "%u", &ring_ref,
			"event-channel", "%u", &evtchn, NULL);
	if (err) {
		xenbus_dev_fatal(dev, err, "reading %s ring", dev->otherend);
		return err;
	}

	return scsiback_init_sring(info, ring_ref, evtchn);
}