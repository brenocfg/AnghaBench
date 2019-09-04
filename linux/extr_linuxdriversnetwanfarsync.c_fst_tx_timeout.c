#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
struct fst_port_info {scalar_t__ start; int /*<<< orphan*/  index; struct fst_card_info* card; } ;
struct fst_card_info {int /*<<< orphan*/  card_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORTTX ; 
 int /*<<< orphan*/  DBG_ASS ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fst_port_info* dev_to_port (struct net_device*) ; 
 int /*<<< orphan*/  fst_issue_cmd (struct fst_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void
fst_tx_timeout(struct net_device *dev)
{
	struct fst_port_info *port;
	struct fst_card_info *card;

	port = dev_to_port(dev);
	card = port->card;
	dev->stats.tx_errors++;
	dev->stats.tx_aborted_errors++;
	dbg(DBG_ASS, "Tx timeout card %d port %d\n",
	    card->card_no, port->index);
	fst_issue_cmd(port, ABORTTX);

	netif_trans_update(dev);
	netif_wake_queue(dev);
	port->start = 0;
}