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
struct visornic_devdata {int num_rcv_bufs; int /*<<< orphan*/ ** rcvbuf; int /*<<< orphan*/  cmdrsp_rcv; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * alloc_rcv_buf (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int post_skb (int /*<<< orphan*/ ,struct visornic_devdata*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_rcv_bufs(struct net_device *netdev,
			 struct visornic_devdata *devdata)
{
	int i, j, count, err;

	/* allocate fixed number of receive buffers to post to uisnic
	 * post receive buffers after we've allocated a required amount
	 */
	for (i = 0; i < devdata->num_rcv_bufs; i++) {
		devdata->rcvbuf[i] = alloc_rcv_buf(netdev);
		/* if we failed to allocate one let us stop */
		if (!devdata->rcvbuf[i])
			break;
	}
	/* couldn't even allocate one -- bail out */
	if (i == 0)
		return -ENOMEM;
	count = i;

	/* Ensure we can alloc 2/3rd of the requested number of buffers.
	 * 2/3 is an arbitrary choice; used also in ndis init.c
	 */
	if (count < ((2 * devdata->num_rcv_bufs) / 3)) {
		/* free receive buffers we did alloc and then bail out */
		for (i = 0; i < count; i++) {
			kfree_skb(devdata->rcvbuf[i]);
			devdata->rcvbuf[i] = NULL;
		}
		return -ENOMEM;
	}

	/* post receive buffers to receive incoming input - without holding
	 * lock - we've not enabled nor started the queue so there shouldn't
	 * be any rcv or xmit activity
	 */
	for (i = 0; i < count; i++) {
		err = post_skb(devdata->cmdrsp_rcv, devdata,
			       devdata->rcvbuf[i]);
		if (!err)
			continue;

		/* Error handling -
		 * If we posted at least one skb, we should return success,
		 * but need to free the resources that we have not successfully
		 * posted.
		 */
		for (j = i; j < count; j++) {
			kfree_skb(devdata->rcvbuf[j]);
			devdata->rcvbuf[j] = NULL;
		}
		if (i == 0)
			return err;
		break;
	}

	return 0;
}