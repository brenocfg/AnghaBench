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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct lapb_cb {int dummy; } ;

/* Variables and functions */
 int LAPB_BADTOKEN ; 
 int LAPB_OK ; 
 int /*<<< orphan*/  lapb_data_input (struct lapb_cb*,struct sk_buff*) ; 
 struct lapb_cb* lapb_devtostruct (struct net_device*) ; 
 int /*<<< orphan*/  lapb_put (struct lapb_cb*) ; 

int lapb_data_received(struct net_device *dev, struct sk_buff *skb)
{
	struct lapb_cb *lapb = lapb_devtostruct(dev);
	int rc = LAPB_BADTOKEN;

	if (lapb) {
		lapb_data_input(lapb, skb);
		lapb_put(lapb);
		rc = LAPB_OK;
	}

	return rc;
}