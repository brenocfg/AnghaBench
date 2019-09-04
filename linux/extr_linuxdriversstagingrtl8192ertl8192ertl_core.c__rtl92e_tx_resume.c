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
struct rtllib_device {scalar_t__ (* check_nic_enough_desc ) (struct net_device*,int) ;int /*<<< orphan*/  (* softmac_data_hard_start_xmit ) (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * skb_waitQ; } ;
struct r8192_priv {struct rtllib_device* rtllib; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BK_QUEUE ; 
 int MAX_QUEUE_SIZE ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct net_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _rtl92e_tx_resume(struct net_device *dev)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct rtllib_device *ieee = priv->rtllib;
	struct sk_buff *skb;
	int queue_index;

	for (queue_index = BK_QUEUE;
	     queue_index < MAX_QUEUE_SIZE; queue_index++) {
		while ((!skb_queue_empty(&ieee->skb_waitQ[queue_index])) &&
		(priv->rtllib->check_nic_enough_desc(dev, queue_index) > 0)) {
			skb = skb_dequeue(&ieee->skb_waitQ[queue_index]);
			ieee->softmac_data_hard_start_xmit(skb, dev, 0);
		}
	}
}