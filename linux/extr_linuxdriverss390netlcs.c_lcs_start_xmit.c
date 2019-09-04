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
struct net_device {scalar_t__ ml_priv; } ;
struct lcs_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int __lcs_start_xmit (struct lcs_card*,struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct lcs_card *card;
	int rc;

	LCS_DBF_TEXT(5, trace, "pktxmit");
	card = (struct lcs_card *) dev->ml_priv;
	rc = __lcs_start_xmit(card, skb, dev);
	return rc;
}