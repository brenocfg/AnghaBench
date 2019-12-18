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
struct xenbus_transaction {int dummy; } ;
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct xen_snd_front_evtchnl {int /*<<< orphan*/  port; int /*<<< orphan*/  gref; TYPE_1__* front_info; } ;
struct TYPE_2__ {struct xenbus_device* xb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int xenbus_printf (struct xenbus_transaction,char const*,char const*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evtchnl_publish(struct xenbus_transaction xbt,
			   struct xen_snd_front_evtchnl *channel,
			   const char *path, const char *node_ring,
			   const char *node_chnl)
{
	struct xenbus_device *xb_dev = channel->front_info->xb_dev;
	int ret;

	/* Write control channel ring reference. */
	ret = xenbus_printf(xbt, path, node_ring, "%u", channel->gref);
	if (ret < 0) {
		dev_err(&xb_dev->dev, "Error writing ring-ref: %d\n", ret);
		return ret;
	}

	/* Write event channel ring reference. */
	ret = xenbus_printf(xbt, path, node_chnl, "%u", channel->port);
	if (ret < 0) {
		dev_err(&xb_dev->dev, "Error writing event channel: %d\n", ret);
		return ret;
	}

	return 0;
}