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
typedef  scalar_t__ u64 ;
struct vgic_its {int /*<<< orphan*/  cmd_lock; scalar_t__ cwriter; int /*<<< orphan*/  cbaser; } ;
struct kvm {int dummy; } ;
typedef  int gpa_t ;

/* Variables and functions */
 scalar_t__ ITS_CMD_BUFFER_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ ITS_CMD_OFFSET (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ update_64bit_reg (scalar_t__,int,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  vgic_its_process_commands (struct kvm*,struct vgic_its*) ; 

__attribute__((used)) static void vgic_mmio_write_its_cwriter(struct kvm *kvm, struct vgic_its *its,
					gpa_t addr, unsigned int len,
					unsigned long val)
{
	u64 reg;

	if (!its)
		return;

	mutex_lock(&its->cmd_lock);

	reg = update_64bit_reg(its->cwriter, addr & 7, len, val);
	reg = ITS_CMD_OFFSET(reg);
	if (reg >= ITS_CMD_BUFFER_SIZE(its->cbaser)) {
		mutex_unlock(&its->cmd_lock);
		return;
	}
	its->cwriter = reg;

	vgic_its_process_commands(kvm, its);

	mutex_unlock(&its->cmd_lock);
}