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
struct vgic_its {int enabled; int baser_device_table; int baser_coll_table; int cbaser; int /*<<< orphan*/  cmd_lock; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int GITS_BASER_VALID ; 
 int GITS_CBASER_VALID ; 
 unsigned long GITS_CTLR_ENABLE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_its_invalidate_cache (struct kvm*) ; 
 int /*<<< orphan*/  vgic_its_process_commands (struct kvm*,struct vgic_its*) ; 

__attribute__((used)) static void vgic_mmio_write_its_ctlr(struct kvm *kvm, struct vgic_its *its,
				     gpa_t addr, unsigned int len,
				     unsigned long val)
{
	mutex_lock(&its->cmd_lock);

	/*
	 * It is UNPREDICTABLE to enable the ITS if any of the CBASER or
	 * device/collection BASER are invalid
	 */
	if (!its->enabled && (val & GITS_CTLR_ENABLE) &&
		(!(its->baser_device_table & GITS_BASER_VALID) ||
		 !(its->baser_coll_table & GITS_BASER_VALID) ||
		 !(its->cbaser & GITS_CBASER_VALID)))
		goto out;

	its->enabled = !!(val & GITS_CTLR_ENABLE);
	if (!its->enabled)
		vgic_its_invalidate_cache(kvm);

	/*
	 * Try to process any pending commands. This function bails out early
	 * if the ITS is disabled or no commands have been queued.
	 */
	vgic_its_process_commands(kvm, its);

out:
	mutex_unlock(&its->cmd_lock);
}