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
struct physdev_unmap_pirq {scalar_t__ domid; int /*<<< orphan*/  pirq; } ;
struct TYPE_3__ {int flags; scalar_t__ domid; int /*<<< orphan*/  pirq; } ;
struct TYPE_4__ {TYPE_1__ pirq; } ;
struct irq_info {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ DOMID_SELF ; 
 int ENOENT ; 
 int ESRCH ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_unmap_pirq*) ; 
 int /*<<< orphan*/  PHYSDEVOP_unmap_pirq ; 
 int PIRQ_MSI_GROUP ; 
 struct irq_info* info_for_irq (int) ; 
 int /*<<< orphan*/  irq_mapping_update_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  xen_free_irq (int) ; 
 scalar_t__ xen_initial_domain () ; 

int xen_destroy_irq(int irq)
{
	struct physdev_unmap_pirq unmap_irq;
	struct irq_info *info = info_for_irq(irq);
	int rc = -ENOENT;

	mutex_lock(&irq_mapping_update_lock);

	/*
	 * If trying to remove a vector in a MSI group different
	 * than the first one skip the PIRQ unmap unless this vector
	 * is the first one in the group.
	 */
	if (xen_initial_domain() && !(info->u.pirq.flags & PIRQ_MSI_GROUP)) {
		unmap_irq.pirq = info->u.pirq.pirq;
		unmap_irq.domid = info->u.pirq.domid;
		rc = HYPERVISOR_physdev_op(PHYSDEVOP_unmap_pirq, &unmap_irq);
		/* If another domain quits without making the pci_disable_msix
		 * call, the Xen hypervisor takes care of freeing the PIRQs
		 * (free_domain_pirqs).
		 */
		if ((rc == -ESRCH && info->u.pirq.domid != DOMID_SELF))
			pr_info("domain %d does not have %d anymore\n",
				info->u.pirq.domid, info->u.pirq.pirq);
		else if (rc) {
			pr_warn("unmap irq failed %d\n", rc);
			goto out;
		}
	}

	xen_free_irq(irq);

out:
	mutex_unlock(&irq_mapping_update_lock);
	return rc;
}