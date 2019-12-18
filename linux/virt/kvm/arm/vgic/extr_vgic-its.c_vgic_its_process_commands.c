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
struct vgic_its {scalar_t__ cwriter; scalar_t__ creadr; int /*<<< orphan*/  cbaser; int /*<<< orphan*/  enabled; } ;
struct kvm {int dummy; } ;
typedef  scalar_t__ gpa_t ;

/* Variables and functions */
 scalar_t__ GITS_CBASER_ADDRESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ITS_CMD_BUFFER_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ ITS_CMD_SIZE ; 
 int kvm_read_guest_lock (struct kvm*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  vgic_its_handle_command (struct kvm*,struct vgic_its*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vgic_its_process_commands(struct kvm *kvm, struct vgic_its *its)
{
	gpa_t cbaser;
	u64 cmd_buf[4];

	/* Commands are only processed when the ITS is enabled. */
	if (!its->enabled)
		return;

	cbaser = GITS_CBASER_ADDRESS(its->cbaser);

	while (its->cwriter != its->creadr) {
		int ret = kvm_read_guest_lock(kvm, cbaser + its->creadr,
					      cmd_buf, ITS_CMD_SIZE);
		/*
		 * If kvm_read_guest() fails, this could be due to the guest
		 * programming a bogus value in CBASER or something else going
		 * wrong from which we cannot easily recover.
		 * According to section 6.3.2 in the GICv3 spec we can just
		 * ignore that command then.
		 */
		if (!ret)
			vgic_its_handle_command(kvm, its, cmd_buf);

		its->creadr += ITS_CMD_SIZE;
		if (its->creadr == ITS_CMD_BUFFER_SIZE(its->cbaser))
			its->creadr = 0;
	}
}