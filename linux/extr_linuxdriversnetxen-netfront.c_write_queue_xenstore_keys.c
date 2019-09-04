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
struct xenbus_device {char* nodename; } ;
struct netfront_queue {int id; int /*<<< orphan*/  rx_evtchn; int /*<<< orphan*/  tx_evtchn; int /*<<< orphan*/  rx_ring_ref; int /*<<< orphan*/  tx_ring_ref; TYPE_1__* info; } ;
struct TYPE_2__ {struct xenbus_device* xbdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*,char const*) ; 
 int xenbus_printf (struct xenbus_transaction,char*,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_queue_xenstore_keys(struct netfront_queue *queue,
			   struct xenbus_transaction *xbt, int write_hierarchical)
{
	/* Write the queue-specific keys into XenStore in the traditional
	 * way for a single queue, or in a queue subkeys for multiple
	 * queues.
	 */
	struct xenbus_device *dev = queue->info->xbdev;
	int err;
	const char *message;
	char *path;
	size_t pathsize;

	/* Choose the correct place to write the keys */
	if (write_hierarchical) {
		pathsize = strlen(dev->nodename) + 10;
		path = kzalloc(pathsize, GFP_KERNEL);
		if (!path) {
			err = -ENOMEM;
			message = "out of memory while writing ring references";
			goto error;
		}
		snprintf(path, pathsize, "%s/queue-%u",
				dev->nodename, queue->id);
	} else {
		path = (char *)dev->nodename;
	}

	/* Write ring references */
	err = xenbus_printf(*xbt, path, "tx-ring-ref", "%u",
			queue->tx_ring_ref);
	if (err) {
		message = "writing tx-ring-ref";
		goto error;
	}

	err = xenbus_printf(*xbt, path, "rx-ring-ref", "%u",
			queue->rx_ring_ref);
	if (err) {
		message = "writing rx-ring-ref";
		goto error;
	}

	/* Write event channels; taking into account both shared
	 * and split event channel scenarios.
	 */
	if (queue->tx_evtchn == queue->rx_evtchn) {
		/* Shared event channel */
		err = xenbus_printf(*xbt, path,
				"event-channel", "%u", queue->tx_evtchn);
		if (err) {
			message = "writing event-channel";
			goto error;
		}
	} else {
		/* Split event channels */
		err = xenbus_printf(*xbt, path,
				"event-channel-tx", "%u", queue->tx_evtchn);
		if (err) {
			message = "writing event-channel-tx";
			goto error;
		}

		err = xenbus_printf(*xbt, path,
				"event-channel-rx", "%u", queue->rx_evtchn);
		if (err) {
			message = "writing event-channel-rx";
			goto error;
		}
	}

	if (write_hierarchical)
		kfree(path);
	return 0;

error:
	if (write_hierarchical)
		kfree(path);
	xenbus_dev_fatal(dev, err, "%s", message);
	return err;
}