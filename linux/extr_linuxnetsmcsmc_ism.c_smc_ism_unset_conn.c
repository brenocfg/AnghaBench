#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smc_connection {TYPE_2__* lgr; TYPE_3__* rmb_desc; } ;
struct TYPE_6__ {size_t sba_idx; } ;
struct TYPE_5__ {TYPE_1__* smcd; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void smc_ism_unset_conn(struct smc_connection *conn)
{
	unsigned long flags;

	if (!conn->rmb_desc)
		return;

	spin_lock_irqsave(&conn->lgr->smcd->lock, flags);
	conn->lgr->smcd->conn[conn->rmb_desc->sba_idx] = NULL;
	spin_unlock_irqrestore(&conn->lgr->smcd->lock, flags);
}