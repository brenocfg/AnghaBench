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
struct vgic_register_region {int dummy; } ;
struct kvm_device_attr {int attr; } ;
struct kvm_device {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENXIO ; 
 int GITS_PIDR4 ; 
 int GITS_TYPER ; 
 int /*<<< orphan*/  its_registers ; 
 struct vgic_register_region* vgic_find_mmio_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vgic_its_has_attr_regs(struct kvm_device *dev,
				  struct kvm_device_attr *attr)
{
	const struct vgic_register_region *region;
	gpa_t offset = attr->attr;
	int align;

	align = (offset < GITS_TYPER) || (offset >= GITS_PIDR4) ? 0x3 : 0x7;

	if (offset & align)
		return -EINVAL;

	region = vgic_find_mmio_region(its_registers,
				       ARRAY_SIZE(its_registers),
				       offset);
	if (!region)
		return -ENXIO;

	return 0;
}