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
typedef  int /*<<< orphan*/  u32 ;
struct vgic_io_device {int /*<<< orphan*/  nr_regions; int /*<<< orphan*/  regions; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int vgic_uaccess (struct kvm_vcpu*,struct vgic_io_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vgic_v3_rd_registers ; 

int vgic_v3_redist_uaccess(struct kvm_vcpu *vcpu, bool is_write,
			   int offset, u32 *val)
{
	struct vgic_io_device rd_dev = {
		.regions = vgic_v3_rd_registers,
		.nr_regions = ARRAY_SIZE(vgic_v3_rd_registers),
	};

	return vgic_uaccess(vcpu, &rd_dev, is_write, offset, val);
}