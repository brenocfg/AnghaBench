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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct rfcomm_dlc {int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  addr; int /*<<< orphan*/  dlci; } ;
struct rfcomm_cmd {int /*<<< orphan*/  fcs; int /*<<< orphan*/  len; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RFCOMM_DISC ; 
 int /*<<< orphan*/  __ctrl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __fcs2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __len8 (int /*<<< orphan*/ ) ; 
 struct rfcomm_cmd* __skb_put (struct sk_buff*,int) ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_schedule () ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int rfcomm_queue_disc(struct rfcomm_dlc *d)
{
	struct rfcomm_cmd *cmd;
	struct sk_buff *skb;

	BT_DBG("dlc %p dlci %d", d, d->dlci);

	skb = alloc_skb(sizeof(*cmd), GFP_KERNEL);
	if (!skb)
		return -ENOMEM;

	cmd = __skb_put(skb, sizeof(*cmd));
	cmd->addr = d->addr;
	cmd->ctrl = __ctrl(RFCOMM_DISC, 1);
	cmd->len  = __len8(0);
	cmd->fcs  = __fcs2((u8 *) cmd);

	skb_queue_tail(&d->tx_queue, skb);
	rfcomm_schedule();
	return 0;
}