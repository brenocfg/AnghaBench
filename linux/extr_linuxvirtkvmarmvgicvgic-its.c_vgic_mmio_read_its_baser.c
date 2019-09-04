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
typedef  int /*<<< orphan*/  u64 ;
struct vgic_its {int /*<<< orphan*/  baser_coll_table; int /*<<< orphan*/  baser_device_table; } ;
struct kvm {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int BASER_INDEX (int) ; 
 unsigned long extract_bytes (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static unsigned long vgic_mmio_read_its_baser(struct kvm *kvm,
					      struct vgic_its *its,
					      gpa_t addr, unsigned int len)
{
	u64 reg;

	switch (BASER_INDEX(addr)) {
	case 0:
		reg = its->baser_device_table;
		break;
	case 1:
		reg = its->baser_coll_table;
		break;
	default:
		reg = 0;
		break;
	}

	return extract_bytes(reg, addr & 7, len);
}