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
struct fnic {int /*<<< orphan*/  tx_queue; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fnic_send_frame (struct fnic*,struct fc_frame*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

void fnic_flush_tx(struct fnic *fnic)
{
	struct sk_buff *skb;
	struct fc_frame *fp;

	while ((skb = skb_dequeue(&fnic->tx_queue))) {
		fp = (struct fc_frame *)skb;
		fnic_send_frame(fnic, fp);
	}
}