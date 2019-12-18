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
struct lec_priv {int dummy; } ;
struct lec_arp_table {int /*<<< orphan*/  usage; int /*<<< orphan*/  tx_wait; struct lec_priv* priv; int /*<<< orphan*/  last_used; int /*<<< orphan*/  timer; int /*<<< orphan*/  next; int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct lec_arp_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lec_arp_expire_arp ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lec_arp_table *make_entry(struct lec_priv *priv,
					const unsigned char *mac_addr)
{
	struct lec_arp_table *to_return;

	to_return = kzalloc(sizeof(struct lec_arp_table), GFP_ATOMIC);
	if (!to_return) {
		pr_info("LEC: Arp entry kmalloc failed\n");
		return NULL;
	}
	ether_addr_copy(to_return->mac_addr, mac_addr);
	INIT_HLIST_NODE(&to_return->next);
	timer_setup(&to_return->timer, lec_arp_expire_arp, 0);
	to_return->last_used = jiffies;
	to_return->priv = priv;
	skb_queue_head_init(&to_return->tx_wait);
	refcount_set(&to_return->usage, 1);
	return to_return;
}