#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_5__ {scalar_t__ modulus; int vr; int vs; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_COMMAND ; 
 unsigned char AX25_EPF ; 
 unsigned char AX25_I ; 
 scalar_t__ AX25_MODULUS ; 
 unsigned char AX25_PF ; 
 int /*<<< orphan*/  ax25_start_idletimer (TYPE_1__*) ; 
 int /*<<< orphan*/  ax25_transmit_buffer (TYPE_1__*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 

__attribute__((used)) static void ax25_send_iframe(ax25_cb *ax25, struct sk_buff *skb, int poll_bit)
{
	unsigned char *frame;

	if (skb == NULL)
		return;

	skb_reset_network_header(skb);

	if (ax25->modulus == AX25_MODULUS) {
		frame = skb_push(skb, 1);

		*frame = AX25_I;
		*frame |= (poll_bit) ? AX25_PF : 0;
		*frame |= (ax25->vr << 5);
		*frame |= (ax25->vs << 1);
	} else {
		frame = skb_push(skb, 2);

		frame[0] = AX25_I;
		frame[0] |= (ax25->vs << 1);
		frame[1] = (poll_bit) ? AX25_EPF : 0;
		frame[1] |= (ax25->vr << 1);
	}

	ax25_start_idletimer(ax25);

	ax25_transmit_buffer(ax25, skb, AX25_COMMAND);
}