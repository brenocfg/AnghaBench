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
struct net_device {int /*<<< orphan*/  flags; scalar_t__ ml_priv; } ;
struct lcs_card {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_STATE_UP ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int lcs_detect (struct lcs_card*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_open_device(struct net_device *dev)
{
	struct lcs_card *card;
	int rc;

	LCS_DBF_TEXT(2, trace, "opendev");
	card = (struct lcs_card *) dev->ml_priv;
	/* initialize statistics */
	rc = lcs_detect(card);
	if (rc) {
		pr_err("Error in opening device!\n");

	} else {
		dev->flags |= IFF_UP;
		netif_carrier_on(dev);
		netif_wake_queue(dev);
		card->state = DEV_STATE_UP;
	}
	return rc;
}