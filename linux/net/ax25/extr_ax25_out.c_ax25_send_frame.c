#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  ax25_digi ;
struct TYPE_19__ {int /*<<< orphan*/  slave; } ;
struct TYPE_20__ {int* values; TYPE_2__ dama; } ;
typedef  TYPE_3__ ax25_dev ;
struct TYPE_21__ {int /*<<< orphan*/  state; TYPE_1__* ax25_dev; int /*<<< orphan*/ * digipeat; void* dest_addr; void* source_addr; } ;
typedef  TYPE_4__ ax25_cb ;
typedef  void* ax25_address ;
struct TYPE_18__ {int* values; } ;

/* Variables and functions */
#define  AX25_PROTO_DAMA_SLAVE 130 
#define  AX25_PROTO_STD_DUPLEX 129 
#define  AX25_PROTO_STD_SIMPLEX 128 
 int /*<<< orphan*/  AX25_STATE_1 ; 
 size_t AX25_VALUES_PACLEN ; 
 size_t AX25_VALUES_PROTOCOL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ax25_cb_add (TYPE_4__*) ; 
 int /*<<< orphan*/  ax25_cb_hold (TYPE_4__*) ; 
 int /*<<< orphan*/  ax25_cb_put (TYPE_4__*) ; 
 TYPE_4__* ax25_create_cb () ; 
 TYPE_3__* ax25_dev_ax25dev (struct net_device*) ; 
 int /*<<< orphan*/  ax25_ds_establish_data_link (TYPE_4__*) ; 
 int /*<<< orphan*/  ax25_fillin_cb (TYPE_4__*,TYPE_3__*) ; 
 TYPE_4__* ax25_find_cb (void**,void**,int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  ax25_output (TYPE_4__*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  ax25_start_heartbeat (TYPE_4__*) ; 
 int /*<<< orphan*/  ax25_std_establish_data_link (TYPE_4__*) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

ax25_cb *ax25_send_frame(struct sk_buff *skb, int paclen, ax25_address *src, ax25_address *dest, ax25_digi *digi, struct net_device *dev)
{
	ax25_dev *ax25_dev;
	ax25_cb *ax25;

	/*
	 * Take the default packet length for the device if zero is
	 * specified.
	 */
	if (paclen == 0) {
		if ((ax25_dev = ax25_dev_ax25dev(dev)) == NULL)
			return NULL;

		paclen = ax25_dev->values[AX25_VALUES_PACLEN];
	}

	/*
	 * Look for an existing connection.
	 */
	if ((ax25 = ax25_find_cb(src, dest, digi, dev)) != NULL) {
		ax25_output(ax25, paclen, skb);
		return ax25;		/* It already existed */
	}

	if ((ax25_dev = ax25_dev_ax25dev(dev)) == NULL)
		return NULL;

	if ((ax25 = ax25_create_cb()) == NULL)
		return NULL;

	ax25_fillin_cb(ax25, ax25_dev);

	ax25->source_addr = *src;
	ax25->dest_addr   = *dest;

	if (digi != NULL) {
		ax25->digipeat = kmemdup(digi, sizeof(*digi), GFP_ATOMIC);
		if (ax25->digipeat == NULL) {
			ax25_cb_put(ax25);
			return NULL;
		}
	}

	switch (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) {
	case AX25_PROTO_STD_SIMPLEX:
	case AX25_PROTO_STD_DUPLEX:
		ax25_std_establish_data_link(ax25);
		break;

#ifdef CONFIG_AX25_DAMA_SLAVE
	case AX25_PROTO_DAMA_SLAVE:
		if (ax25_dev->dama.slave)
			ax25_ds_establish_data_link(ax25);
		else
			ax25_std_establish_data_link(ax25);
		break;
#endif
	}

	/*
	 * There is one ref for the state machine; a caller needs
	 * one more to put it back, just like with the existing one.
	 */
	ax25_cb_hold(ax25);

	ax25_cb_add(ax25);

	ax25->state = AX25_STATE_1;

	ax25_start_heartbeat(ax25);

	ax25_output(ax25, paclen, skb);

	return ax25;			/* We had to create it */
}