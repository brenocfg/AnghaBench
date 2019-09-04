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
typedef  int /*<<< orphan*/  u8 ;
struct fnic {int /*<<< orphan*/  fnic_lock; } ;
struct fc_lport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fnic_update_mac_locked (struct fnic*,int /*<<< orphan*/ *) ; 
 struct fnic* lport_priv (struct fc_lport*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void fnic_update_mac(struct fc_lport *lport, u8 *new)
{
	struct fnic *fnic = lport_priv(lport);

	spin_lock_irq(&fnic->fnic_lock);
	fnic_update_mac_locked(fnic, new);
	spin_unlock_irq(&fnic->fnic_lock);
}