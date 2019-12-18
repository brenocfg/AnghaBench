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
typedef  unsigned long long u64 ;
struct vgic_its {TYPE_1__* dev; } ;
struct its_collection {unsigned long long collection_id; scalar_t__ target_addr; } ;
typedef  int /*<<< orphan*/  gpa_t ;
struct TYPE_2__ {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 unsigned long long KVM_ITS_CTE_RDBASE_SHIFT ; 
 unsigned long long KVM_ITS_CTE_VALID_SHIFT ; 
 unsigned long long cpu_to_le64 (unsigned long long) ; 
 int kvm_write_guest_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*,int) ; 

__attribute__((used)) static int vgic_its_save_cte(struct vgic_its *its,
			     struct its_collection *collection,
			     gpa_t gpa, int esz)
{
	u64 val;

	val = (1ULL << KVM_ITS_CTE_VALID_SHIFT |
	       ((u64)collection->target_addr << KVM_ITS_CTE_RDBASE_SHIFT) |
	       collection->collection_id);
	val = cpu_to_le64(val);
	return kvm_write_guest_lock(its->dev->kvm, gpa, &val, esz);
}