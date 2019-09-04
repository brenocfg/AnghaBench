#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  flags; scalar_t__ ml_priv; } ;
struct TYPE_4__ {scalar_t__ state; int /*<<< orphan*/  wait_q; } ;
struct lcs_card {TYPE_1__* dev; TYPE_2__ write; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_UP ; 
 scalar_t__ LCS_CH_STATE_RUNNING ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lcs_stopcard (struct lcs_card*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  trace ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
lcs_stop_device(struct net_device *dev)
{
	struct lcs_card *card;
	int rc;

	LCS_DBF_TEXT(2, trace, "stopdev");
	card   = (struct lcs_card *) dev->ml_priv;
	netif_carrier_off(dev);
	netif_tx_disable(dev);
	dev->flags &= ~IFF_UP;
	wait_event(card->write.wait_q,
		(card->write.state != LCS_CH_STATE_RUNNING));
	rc = lcs_stopcard(card);
	if (rc)
		dev_err(&card->dev->dev,
			" Shutting down the LCS device failed\n");
	return rc;
}