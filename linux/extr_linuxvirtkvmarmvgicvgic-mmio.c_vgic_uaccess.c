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
struct vgic_io_device {int /*<<< orphan*/  dev; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int vgic_uaccess_read (struct kvm_vcpu*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int vgic_uaccess_write (struct kvm_vcpu*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int vgic_uaccess(struct kvm_vcpu *vcpu, struct vgic_io_device *dev,
		 bool is_write, int offset, u32 *val)
{
	if (is_write)
		return vgic_uaccess_write(vcpu, &dev->dev, offset, val);
	else
		return vgic_uaccess_read(vcpu, &dev->dev, offset, val);
}