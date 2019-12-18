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
struct vgic_irq {int dummy; } ;
struct seq_file {int dummy; } ;
struct kvm_vcpu {int vcpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void print_header(struct seq_file *s, struct vgic_irq *irq,
			 struct kvm_vcpu *vcpu)
{
	int id = 0;
	char *hdr = "SPI ";

	if (vcpu) {
		hdr = "VCPU";
		id = vcpu->vcpu_id;
	}

	seq_printf(s, "\n");
	seq_printf(s, "%s%2d TYP   ID TGT_ID PLAEHCG     HWID   TARGET SRC PRI VCPU_ID\n", hdr, id);
	seq_printf(s, "----------------------------------------------------------------\n");
}