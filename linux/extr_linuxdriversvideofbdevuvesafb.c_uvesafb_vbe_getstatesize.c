#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uvesafb_par {int vbe_state_size; } ;
struct TYPE_3__ {int eax; int ecx; int edx; int ebx; } ;
struct TYPE_4__ {TYPE_1__ regs; scalar_t__ flags; } ;
struct uvesafb_ktask {TYPE_2__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_reset (struct uvesafb_ktask*) ; 

__attribute__((used)) static void uvesafb_vbe_getstatesize(struct uvesafb_ktask *task,
				     struct uvesafb_par *par)
{
	int err;

	uvesafb_reset(task);

	/*
	 * Get the VBE state buffer size. We want all available
	 * hardware state data (CL = 0x0f).
	 */
	task->t.regs.eax = 0x4f04;
	task->t.regs.ecx = 0x000f;
	task->t.regs.edx = 0x0000;
	task->t.flags = 0;

	err = uvesafb_exec(task);

	if (err || (task->t.regs.eax & 0xffff) != 0x004f) {
		pr_warn("VBE state buffer size cannot be determined (eax=0x%x, err=%d)\n",
			task->t.regs.eax, err);
		par->vbe_state_size = 0;
		return;
	}

	par->vbe_state_size = 64 * (task->t.regs.ebx & 0xffff);
}