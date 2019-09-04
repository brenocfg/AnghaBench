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
typedef  scalar_t__ u8 ;
struct slot {scalar_t__ state; int /*<<< orphan*/  lock; } ;
struct controller {int /*<<< orphan*/  reset_lock; struct slot* slot; } ;

/* Variables and functions */
 scalar_t__ BLINKINGOFF_STATE ; 
 scalar_t__ BLINKINGON_STATE ; 
 scalar_t__ OFF_STATE ; 
 scalar_t__ ON_STATE ; 
 int /*<<< orphan*/  PCI_EXP_SLTSTA_PDC ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_get_adapter_status (struct slot*,scalar_t__*) ; 
 int /*<<< orphan*/  pciehp_request (struct controller*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pciehp_check_presence(struct controller *ctrl)
{
	struct slot *slot = ctrl->slot;
	u8 occupied;

	down_read(&ctrl->reset_lock);
	mutex_lock(&slot->lock);

	pciehp_get_adapter_status(slot, &occupied);
	if ((occupied && (slot->state == OFF_STATE ||
			  slot->state == BLINKINGON_STATE)) ||
	    (!occupied && (slot->state == ON_STATE ||
			   slot->state == BLINKINGOFF_STATE)))
		pciehp_request(ctrl, PCI_EXP_SLTSTA_PDC);

	mutex_unlock(&slot->lock);
	up_read(&ctrl->reset_lock);
}