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
typedef  int u64 ;
struct vgic_its_abi {int dte_esz; int cte_esz; } ;
struct vgic_its {int baser_device_table; int baser_coll_table; int /*<<< orphan*/  its_lock; scalar_t__ enabled; } ;
struct kvm {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int BASER_INDEX (int) ; 
 int GITS_BASER_ENTRY_SIZE_SHIFT ; 
 int GITS_BASER_INDIRECT ; 
 int GITS_BASER_RO_MASK ; 
#define  GITS_BASER_TYPE_COLLECTION 129 
#define  GITS_BASER_TYPE_DEVICE 128 
 int GITS_BASER_TYPE_SHIFT ; 
 int GITS_BASER_VALID ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int update_64bit_reg (int,int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  vgic_its_free_collection_list (struct kvm*,struct vgic_its*) ; 
 int /*<<< orphan*/  vgic_its_free_device_list (struct kvm*,struct vgic_its*) ; 
 struct vgic_its_abi* vgic_its_get_abi (struct vgic_its*) ; 
 int vgic_sanitise_its_baser (int) ; 

__attribute__((used)) static void vgic_mmio_write_its_baser(struct kvm *kvm,
				      struct vgic_its *its,
				      gpa_t addr, unsigned int len,
				      unsigned long val)
{
	const struct vgic_its_abi *abi = vgic_its_get_abi(its);
	u64 entry_size, table_type;
	u64 reg, *regptr, clearbits = 0;

	/* When GITS_CTLR.Enable is 1, we ignore write accesses. */
	if (its->enabled)
		return;

	switch (BASER_INDEX(addr)) {
	case 0:
		regptr = &its->baser_device_table;
		entry_size = abi->dte_esz;
		table_type = GITS_BASER_TYPE_DEVICE;
		break;
	case 1:
		regptr = &its->baser_coll_table;
		entry_size = abi->cte_esz;
		table_type = GITS_BASER_TYPE_COLLECTION;
		clearbits = GITS_BASER_INDIRECT;
		break;
	default:
		return;
	}

	reg = update_64bit_reg(*regptr, addr & 7, len, val);
	reg &= ~GITS_BASER_RO_MASK;
	reg &= ~clearbits;

	reg |= (entry_size - 1) << GITS_BASER_ENTRY_SIZE_SHIFT;
	reg |= table_type << GITS_BASER_TYPE_SHIFT;
	reg = vgic_sanitise_its_baser(reg);

	*regptr = reg;

	if (!(reg & GITS_BASER_VALID)) {
		/* Take the its_lock to prevent a race with a save/restore */
		mutex_lock(&its->its_lock);
		switch (table_type) {
		case GITS_BASER_TYPE_DEVICE:
			vgic_its_free_device_list(kvm, its);
			break;
		case GITS_BASER_TYPE_COLLECTION:
			vgic_its_free_collection_list(kvm, its);
			break;
		}
		mutex_unlock(&its->its_lock);
	}
}