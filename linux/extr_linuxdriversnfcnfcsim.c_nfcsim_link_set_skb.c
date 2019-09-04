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
typedef  void* u8 ;
struct sk_buff {int dummy; } ;
struct nfcsim_link {int /*<<< orphan*/  lock; void* mode; void* rf_tech; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfcsim_link_set_skb(struct nfcsim_link *link, struct sk_buff *skb,
				u8 rf_tech, u8 mode)
{
	mutex_lock(&link->lock);

	dev_kfree_skb(link->skb);
	link->skb = skb;
	link->rf_tech = rf_tech;
	link->mode = mode;

	mutex_unlock(&link->lock);
}