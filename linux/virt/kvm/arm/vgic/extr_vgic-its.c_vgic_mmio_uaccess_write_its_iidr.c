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
typedef  scalar_t__ u32 ;
struct vgic_its {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GITS_IIDR_REV (unsigned long) ; 
 scalar_t__ NR_ITS_ABIS ; 
 int vgic_its_set_abi (struct vgic_its*,scalar_t__) ; 

__attribute__((used)) static int vgic_mmio_uaccess_write_its_iidr(struct kvm *kvm,
					    struct vgic_its *its,
					    gpa_t addr, unsigned int len,
					    unsigned long val)
{
	u32 rev = GITS_IIDR_REV(val);

	if (rev >= NR_ITS_ABIS)
		return -EINVAL;
	return vgic_its_set_abi(its, rev);
}