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
struct smcd_dev {int /*<<< orphan*/  lock; struct smc_connection** conn; } ;
struct smc_connection {int /*<<< orphan*/  rx_tsklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void smcd_handle_irq(struct smcd_dev *smcd, unsigned int dmbno)
{
	struct smc_connection *conn = NULL;
	unsigned long flags;

	spin_lock_irqsave(&smcd->lock, flags);
	conn = smcd->conn[dmbno];
	if (conn)
		tasklet_schedule(&conn->rx_tsklet);
	spin_unlock_irqrestore(&smcd->lock, flags);
}