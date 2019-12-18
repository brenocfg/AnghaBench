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
struct vgic_its {int /*<<< orphan*/  creadr; } ;
struct kvm {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 unsigned long extract_bytes (int /*<<< orphan*/ ,int,unsigned int) ; 

__attribute__((used)) static unsigned long vgic_mmio_read_its_creadr(struct kvm *kvm,
					       struct vgic_its *its,
					       gpa_t addr, unsigned int len)
{
	return extract_bytes(its->creadr, addr & 0x7, len);
}