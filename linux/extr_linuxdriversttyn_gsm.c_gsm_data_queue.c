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
struct gsm_msg {int dummy; } ;
struct gsm_dlci {TYPE_1__* gsm; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gsm_data_queue (struct gsm_dlci*,struct gsm_msg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gsm_data_queue(struct gsm_dlci *dlci, struct gsm_msg *msg)
{
	unsigned long flags;
	spin_lock_irqsave(&dlci->gsm->tx_lock, flags);
	__gsm_data_queue(dlci, msg);
	spin_unlock_irqrestore(&dlci->gsm->tx_lock, flags);
}