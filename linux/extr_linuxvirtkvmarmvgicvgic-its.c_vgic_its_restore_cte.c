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
typedef  int /*<<< orphan*/  val ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct vgic_its {TYPE_1__* dev; } ;
struct kvm {int /*<<< orphan*/  online_vcpus; } ;
struct its_collection {scalar_t__ target_addr; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_2__ {struct kvm* kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EEXIST ; 
 int EINVAL ; 
 scalar_t__ KVM_ITS_CTE_ICID_MASK ; 
 scalar_t__ KVM_ITS_CTE_RDBASE_SHIFT ; 
 scalar_t__ KVM_ITS_CTE_VALID_MASK ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct its_collection* find_collection (struct vgic_its*,scalar_t__) ; 
 int kvm_read_guest_lock (struct kvm*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ le64_to_cpu (scalar_t__) ; 
 int vgic_its_alloc_collection (struct vgic_its*,struct its_collection**,scalar_t__) ; 

__attribute__((used)) static int vgic_its_restore_cte(struct vgic_its *its, gpa_t gpa, int esz)
{
	struct its_collection *collection;
	struct kvm *kvm = its->dev->kvm;
	u32 target_addr, coll_id;
	u64 val;
	int ret;

	BUG_ON(esz > sizeof(val));
	ret = kvm_read_guest_lock(kvm, gpa, &val, esz);
	if (ret)
		return ret;
	val = le64_to_cpu(val);
	if (!(val & KVM_ITS_CTE_VALID_MASK))
		return 0;

	target_addr = (u32)(val >> KVM_ITS_CTE_RDBASE_SHIFT);
	coll_id = val & KVM_ITS_CTE_ICID_MASK;

	if (target_addr >= atomic_read(&kvm->online_vcpus))
		return -EINVAL;

	collection = find_collection(its, coll_id);
	if (collection)
		return -EEXIST;
	ret = vgic_its_alloc_collection(its, &collection, coll_id);
	if (ret)
		return ret;
	collection->target_addr = target_addr;
	return 1;
}