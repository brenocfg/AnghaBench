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
struct vgic_its {int /*<<< orphan*/  cmd_lock; scalar_t__ creadr; scalar_t__ cwriter; int /*<<< orphan*/  cbaser; scalar_t__ enabled; } ;
struct kvm {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_64bit_reg (int /*<<< orphan*/ ,int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  vgic_sanitise_its_cbaser (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vgic_mmio_write_its_cbaser(struct kvm *kvm, struct vgic_its *its,
				       gpa_t addr, unsigned int len,
				       unsigned long val)
{
	/* When GITS_CTLR.Enable is 1, this register is RO. */
	if (its->enabled)
		return;

	mutex_lock(&its->cmd_lock);
	its->cbaser = update_64bit_reg(its->cbaser, addr & 7, len, val);
	its->cbaser = vgic_sanitise_its_cbaser(its->cbaser);
	its->creadr = 0;
	/*
	 * CWRITER is architecturally UNKNOWN on reset, but we need to reset
	 * it to CREADR to make sure we start with an empty command buffer.
	 */
	its->cwriter = its->creadr;
	mutex_unlock(&its->cmd_lock);
}