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
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {scalar_t__ cr; int /*<<< orphan*/ * control; } ;
struct lapb_cb {int mode; int vs; int vr; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; int /*<<< orphan*/  frmr_type; TYPE_1__ frmr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int LAPB_EXTENDED ; 
 void* LAPB_FRMR ; 
 scalar_t__ LAPB_HEADER_LEN ; 
 scalar_t__ LAPB_RESPONSE ; 
 struct sk_buff* alloc_skb (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lapb_dbg (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lapb_transmit_buffer (struct lapb_cb*,struct sk_buff*,scalar_t__) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 

void lapb_transmit_frmr(struct lapb_cb *lapb)
{
	struct sk_buff *skb;
	unsigned char  *dptr;

	if ((skb = alloc_skb(LAPB_HEADER_LEN + 7, GFP_ATOMIC)) == NULL)
		return;

	skb_reserve(skb, LAPB_HEADER_LEN + 1);

	if (lapb->mode & LAPB_EXTENDED) {
		dptr    = skb_put(skb, 6);
		*dptr++ = LAPB_FRMR;
		*dptr++ = lapb->frmr_data.control[0];
		*dptr++ = lapb->frmr_data.control[1];
		*dptr++ = (lapb->vs << 1) & 0xFE;
		*dptr   = (lapb->vr << 1) & 0xFE;
		if (lapb->frmr_data.cr == LAPB_RESPONSE)
			*dptr |= 0x01;
		dptr++;
		*dptr++ = lapb->frmr_type;

		lapb_dbg(1, "(%p) S%d TX FRMR %5ph\n",
			 lapb->dev, lapb->state,
			 &skb->data[1]);
	} else {
		dptr    = skb_put(skb, 4);
		*dptr++ = LAPB_FRMR;
		*dptr++ = lapb->frmr_data.control[0];
		*dptr   = (lapb->vs << 1) & 0x0E;
		*dptr  |= (lapb->vr << 5) & 0xE0;
		if (lapb->frmr_data.cr == LAPB_RESPONSE)
			*dptr |= 0x10;
		dptr++;
		*dptr++ = lapb->frmr_type;

		lapb_dbg(1, "(%p) S%d TX FRMR %3ph\n",
			 lapb->dev, lapb->state, &skb->data[1]);
	}

	lapb_transmit_buffer(lapb, skb, LAPB_RESPONSE);
}