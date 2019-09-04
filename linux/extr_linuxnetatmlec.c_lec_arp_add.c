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
struct lec_priv {struct hlist_head* lec_arp_tables; } ;
struct lec_arp_table {int /*<<< orphan*/ * mac_addr; int /*<<< orphan*/  next; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 size_t HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,struct hlist_head*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
lec_arp_add(struct lec_priv *priv, struct lec_arp_table *entry)
{
	struct hlist_head *tmp;

	tmp = &priv->lec_arp_tables[HASH(entry->mac_addr[ETH_ALEN - 1])];
	hlist_add_head(&entry->next, tmp);

	pr_debug("Added entry:%pM\n", entry->mac_addr);
}