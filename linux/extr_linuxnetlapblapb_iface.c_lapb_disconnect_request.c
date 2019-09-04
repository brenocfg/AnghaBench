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
struct lapb_cb {int state; int /*<<< orphan*/  dev; scalar_t__ n2count; } ;

/* Variables and functions */
 int LAPB_BADTOKEN ; 
 int /*<<< orphan*/  LAPB_COMMAND ; 
 int /*<<< orphan*/  LAPB_DISC ; 
 int LAPB_NOTCONNECTED ; 
 int LAPB_OK ; 
 int /*<<< orphan*/  LAPB_POLLON ; 
#define  LAPB_STATE_0 130 
#define  LAPB_STATE_1 129 
#define  LAPB_STATE_2 128 
 int /*<<< orphan*/  lapb_clear_queues (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_dbg (int,char*,int /*<<< orphan*/ ) ; 
 struct lapb_cb* lapb_devtostruct (struct net_device*) ; 
 int /*<<< orphan*/  lapb_put (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_send_control (struct lapb_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_start_t1timer (struct lapb_cb*) ; 
 int /*<<< orphan*/  lapb_stop_t2timer (struct lapb_cb*) ; 

int lapb_disconnect_request(struct net_device *dev)
{
	struct lapb_cb *lapb = lapb_devtostruct(dev);
	int rc = LAPB_BADTOKEN;

	if (!lapb)
		goto out;

	switch (lapb->state) {
	case LAPB_STATE_0:
		rc = LAPB_NOTCONNECTED;
		goto out_put;

	case LAPB_STATE_1:
		lapb_dbg(1, "(%p) S1 TX DISC(1)\n", lapb->dev);
		lapb_dbg(0, "(%p) S1 -> S0\n", lapb->dev);
		lapb_send_control(lapb, LAPB_DISC, LAPB_POLLON, LAPB_COMMAND);
		lapb->state = LAPB_STATE_0;
		lapb_start_t1timer(lapb);
		rc = LAPB_NOTCONNECTED;
		goto out_put;

	case LAPB_STATE_2:
		rc = LAPB_OK;
		goto out_put;
	}

	lapb_clear_queues(lapb);
	lapb->n2count = 0;
	lapb_send_control(lapb, LAPB_DISC, LAPB_POLLON, LAPB_COMMAND);
	lapb_start_t1timer(lapb);
	lapb_stop_t2timer(lapb);
	lapb->state = LAPB_STATE_2;

	lapb_dbg(1, "(%p) S3 DISC(1)\n", lapb->dev);
	lapb_dbg(0, "(%p) S3 -> S2\n", lapb->dev);

	rc = LAPB_OK;
out_put:
	lapb_put(lapb);
out:
	return rc;
}