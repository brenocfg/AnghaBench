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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct vgic_its {TYPE_1__* dev; } ;
struct its_device {int dummy; } ;
typedef  int gpa_t ;
struct TYPE_2__ {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct its_device*) ; 
 int KVM_ITS_DTE_ITTADDR_MASK ; 
 int KVM_ITS_DTE_ITTADDR_SHIFT ; 
 int KVM_ITS_DTE_NEXT_MASK ; 
 int KVM_ITS_DTE_NEXT_SHIFT ; 
 int KVM_ITS_DTE_SIZE_MASK ; 
 int KVM_ITS_DTE_VALID_SHIFT ; 
 int PTR_ERR (struct its_device*) ; 
 int le64_to_cpu (int) ; 
 struct its_device* vgic_its_alloc_device (struct vgic_its*,int,int,int) ; 
 int /*<<< orphan*/  vgic_its_free_device (int /*<<< orphan*/ ,struct its_device*) ; 
 int vgic_its_restore_itt (struct vgic_its*,struct its_device*) ; 

__attribute__((used)) static int vgic_its_restore_dte(struct vgic_its *its, u32 id,
				void *ptr, void *opaque)
{
	struct its_device *dev;
	gpa_t itt_addr;
	u8 num_eventid_bits;
	u64 entry = *(u64 *)ptr;
	bool valid;
	u32 offset;
	int ret;

	entry = le64_to_cpu(entry);

	valid = entry >> KVM_ITS_DTE_VALID_SHIFT;
	num_eventid_bits = (entry & KVM_ITS_DTE_SIZE_MASK) + 1;
	itt_addr = ((entry & KVM_ITS_DTE_ITTADDR_MASK)
			>> KVM_ITS_DTE_ITTADDR_SHIFT) << 8;

	if (!valid)
		return 1;

	/* dte entry is valid */
	offset = (entry & KVM_ITS_DTE_NEXT_MASK) >> KVM_ITS_DTE_NEXT_SHIFT;

	dev = vgic_its_alloc_device(its, id, itt_addr, num_eventid_bits);
	if (IS_ERR(dev))
		return PTR_ERR(dev);

	ret = vgic_its_restore_itt(its, dev);
	if (ret) {
		vgic_its_free_device(its->dev->kvm, dev);
		return ret;
	}

	return offset;
}