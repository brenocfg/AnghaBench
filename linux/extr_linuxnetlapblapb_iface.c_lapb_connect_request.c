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
struct net_device {int dummy; } ;
struct lapb_cb {scalar_t__ state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int LAPB_BADTOKEN ; 
 int LAPB_CONNECTED ; 
 int LAPB_OK ; 
 scalar_t__ LAPB_STATE_1 ; 
 scalar_t__ LAPB_STATE_3 ; 
 scalar_t__ LAPB_STATE_4 ; 
 int /*<<< orphan*/  lapb_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct lapb_cb* lapb_devtostruct (struct net_device*) ; 
 int /*<<< orphan*/  lapb_establish_data_link (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_put (struct lapb_cb*) ; 

int lapb_connect_request(struct net_device *dev)
{
	struct lapb_cb *lapb = lapb_devtostruct(dev);
	int rc = LAPB_BADTOKEN;

	if (!lapb)
		goto out;

	rc = LAPB_OK;
	if (lapb->state == LAPB_STATE_1)
		goto out_put;

	rc = LAPB_CONNECTED;
	if (lapb->state == LAPB_STATE_3 || lapb->state == LAPB_STATE_4)
		goto out_put;

	lapb_establish_data_link(lapb);

	lapb_dbg(0, "(%p) S0 -> S1\n", lapb->dev);
	lapb->state = LAPB_STATE_1;

	rc = LAPB_OK;
out_put:
	lapb_put(lapb);
out:
	return rc;
}