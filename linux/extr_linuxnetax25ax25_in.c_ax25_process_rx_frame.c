#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_6__ {scalar_t__ state; TYPE_1__* ax25_dev; } ;
typedef  TYPE_2__ ax25_cb ;
struct TYPE_5__ {int* values; } ;

/* Variables and functions */
#define  AX25_PROTO_STD_DUPLEX 129 
#define  AX25_PROTO_STD_SIMPLEX 128 
 scalar_t__ AX25_STATE_0 ; 
 size_t AX25_VALUES_PROTOCOL ; 
 int ax25_std_frame_in (TYPE_2__*,struct sk_buff*,int) ; 

__attribute__((used)) static int ax25_process_rx_frame(ax25_cb *ax25, struct sk_buff *skb, int type, int dama)
{
	int queued = 0;

	if (ax25->state == AX25_STATE_0)
		return 0;

	switch (ax25->ax25_dev->values[AX25_VALUES_PROTOCOL]) {
	case AX25_PROTO_STD_SIMPLEX:
	case AX25_PROTO_STD_DUPLEX:
		queued = ax25_std_frame_in(ax25, skb, type);
		break;

#ifdef CONFIG_AX25_DAMA_SLAVE
	case AX25_PROTO_DAMA_SLAVE:
		if (dama || ax25->ax25_dev->dama.slave)
			queued = ax25_ds_frame_in(ax25, skb, type);
		else
			queued = ax25_std_frame_in(ax25, skb, type);
		break;
#endif
	}

	return queued;
}