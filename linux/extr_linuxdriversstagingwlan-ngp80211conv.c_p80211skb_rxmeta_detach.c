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
struct sk_buff {int /*<<< orphan*/  cb; } ;
struct p80211_rxmeta {int dummy; } ;
struct p80211_frmmeta {struct p80211_rxmeta* rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct p80211_rxmeta*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct p80211_frmmeta* p80211skb_frmmeta (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void p80211skb_rxmeta_detach(struct sk_buff *skb)
{
	struct p80211_rxmeta *rxmeta;
	struct p80211_frmmeta *frmmeta;

	/* Sanity checks */
	if (!skb) {	/* bad skb */
		pr_debug("Called w/ null skb.\n");
		return;
	}
	frmmeta = p80211skb_frmmeta(skb);
	if (!frmmeta) {	/* no magic */
		pr_debug("Called w/ bad frmmeta magic.\n");
		return;
	}
	rxmeta = frmmeta->rx;
	if (!rxmeta) {	/* bad meta ptr */
		pr_debug("Called w/ bad rxmeta ptr.\n");
		return;
	}

	/* Free rxmeta */
	kfree(rxmeta);

	/* Clear skb->cb */
	memset(skb->cb, 0, sizeof(skb->cb));
}