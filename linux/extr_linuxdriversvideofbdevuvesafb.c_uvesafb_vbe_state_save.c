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
typedef  int /*<<< orphan*/  u8 ;
struct uvesafb_par {scalar_t__ vbe_state_size; } ;
struct TYPE_3__ {int eax; int ecx; int edx; } ;
struct TYPE_4__ {int flags; TYPE_1__ regs; scalar_t__ buf_len; } ;
struct uvesafb_ktask {TYPE_2__ t; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TF_BUF_ESBX ; 
 int TF_BUF_RET ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_free (struct uvesafb_ktask*) ; 
 struct uvesafb_ktask* uvesafb_prep () ; 

__attribute__((used)) static u8 *uvesafb_vbe_state_save(struct uvesafb_par *par)
{
	struct uvesafb_ktask *task;
	u8 *state;
	int err;

	if (!par->vbe_state_size)
		return NULL;

	state = kmalloc(par->vbe_state_size, GFP_KERNEL);
	if (!state)
		return ERR_PTR(-ENOMEM);

	task = uvesafb_prep();
	if (!task) {
		kfree(state);
		return NULL;
	}

	task->t.regs.eax = 0x4f04;
	task->t.regs.ecx = 0x000f;
	task->t.regs.edx = 0x0001;
	task->t.flags = TF_BUF_RET | TF_BUF_ESBX;
	task->t.buf_len = par->vbe_state_size;
	task->buf = state;
	err = uvesafb_exec(task);

	if (err || (task->t.regs.eax & 0xffff) != 0x004f) {
		pr_warn("VBE get state call failed (eax=0x%x, err=%d)\n",
			task->t.regs.eax, err);
		kfree(state);
		state = NULL;
	}

	uvesafb_free(task);
	return state;
}