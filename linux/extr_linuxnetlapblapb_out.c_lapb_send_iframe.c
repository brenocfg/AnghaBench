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
struct lapb_cb {int mode; int vs; int vr; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAPB_COMMAND ; 
 unsigned char LAPB_EPF ; 
 int LAPB_EXTENDED ; 
 unsigned char LAPB_I ; 
 unsigned char LAPB_SPF ; 
 int /*<<< orphan*/  lapb_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  lapb_transmit_buffer (struct lapb_cb*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void lapb_send_iframe(struct lapb_cb *lapb, struct sk_buff *skb, int poll_bit)
{
	unsigned char *frame;

	if (!skb)
		return;

	if (lapb->mode & LAPB_EXTENDED) {
		frame = skb_push(skb, 2);

		frame[0] = LAPB_I;
		frame[0] |= lapb->vs << 1;
		frame[1] = poll_bit ? LAPB_EPF : 0;
		frame[1] |= lapb->vr << 1;
	} else {
		frame = skb_push(skb, 1);

		*frame = LAPB_I;
		*frame |= poll_bit ? LAPB_SPF : 0;
		*frame |= lapb->vr << 5;
		*frame |= lapb->vs << 1;
	}

	lapb_dbg(1, "(%p) S%d TX I(%d) S%d R%d\n",
		 lapb->dev, lapb->state, poll_bit, lapb->vs, lapb->vr);

	lapb_transmit_buffer(lapb, skb, LAPB_COMMAND);
}