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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  DriverLock; } ;
struct s_smc {TYPE_1__ os; } ;
typedef  TYPE_1__ skfddi_priv ;

/* Variables and functions */
 int /*<<< orphan*/  netif_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  send_queued_packets (struct s_smc*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void llc_restart_tx(struct s_smc *smc)
{
	skfddi_priv *bp = &smc->os;

	pr_debug("[llc_restart_tx]\n");

	// Try to send queued packets
	spin_unlock(&bp->DriverLock);
	send_queued_packets(smc);
	spin_lock(&bp->DriverLock);
	netif_start_queue(bp->dev);// system may send again if it was blocked

}