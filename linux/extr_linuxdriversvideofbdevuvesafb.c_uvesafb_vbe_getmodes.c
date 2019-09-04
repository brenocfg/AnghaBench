#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct vbe_mode_ib {int mode_id; int mode_attr; int bits_per_pixel; int depth; int red_len; int green_len; int blue_len; } ;
struct TYPE_4__ {int mode_list_ptr; } ;
struct uvesafb_par {scalar_t__ vbe_modes_cnt; struct vbe_mode_ib* vbe_modes; TYPE_1__ vbe_ib; } ;
struct TYPE_5__ {int eax; scalar_t__ ecx; } ;
struct TYPE_6__ {int flags; int buf_len; TYPE_2__ regs; } ;
struct uvesafb_ktask {struct vbe_mode_ib* buf; TYPE_3__ t; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TF_BUF_ESDI ; 
 int TF_BUF_RET ; 
 int VBE_MODE_MASK ; 
 struct vbe_mode_ib* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int,scalar_t__,int) ; 
 int uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_reset (struct uvesafb_ktask*) ; 

__attribute__((used)) static int uvesafb_vbe_getmodes(struct uvesafb_ktask *task,
				struct uvesafb_par *par)
{
	int off = 0, err;
	u16 *mode;

	par->vbe_modes_cnt = 0;

	/* Count available modes. */
	mode = (u16 *) (((u8 *)&par->vbe_ib) + par->vbe_ib.mode_list_ptr);
	while (*mode != 0xffff) {
		par->vbe_modes_cnt++;
		mode++;
	}

	par->vbe_modes = kcalloc(par->vbe_modes_cnt,
				 sizeof(struct vbe_mode_ib),
				 GFP_KERNEL);
	if (!par->vbe_modes)
		return -ENOMEM;

	/* Get info about all available modes. */
	mode = (u16 *) (((u8 *)&par->vbe_ib) + par->vbe_ib.mode_list_ptr);
	while (*mode != 0xffff) {
		struct vbe_mode_ib *mib;

		uvesafb_reset(task);
		task->t.regs.eax = 0x4f01;
		task->t.regs.ecx = (u32) *mode;
		task->t.flags = TF_BUF_RET | TF_BUF_ESDI;
		task->t.buf_len = sizeof(struct vbe_mode_ib);
		task->buf = par->vbe_modes + off;

		err = uvesafb_exec(task);
		if (err || (task->t.regs.eax & 0xffff) != 0x004f) {
			pr_warn("Getting mode info block for mode 0x%x failed (eax=0x%x, err=%d)\n",
				*mode, (u32)task->t.regs.eax, err);
			mode++;
			par->vbe_modes_cnt--;
			continue;
		}

		mib = task->buf;
		mib->mode_id = *mode;

		/*
		 * We only want modes that are supported with the current
		 * hardware configuration, color, graphics and that have
		 * support for the LFB.
		 */
		if ((mib->mode_attr & VBE_MODE_MASK) == VBE_MODE_MASK &&
				 mib->bits_per_pixel >= 8)
			off++;
		else
			par->vbe_modes_cnt--;

		mode++;
		mib->depth = mib->red_len + mib->green_len + mib->blue_len;

		/*
		 * Handle 8bpp modes and modes with broken color component
		 * lengths.
		 */
		if (mib->depth == 0 || (mib->depth == 24 &&
					mib->bits_per_pixel == 32))
			mib->depth = mib->bits_per_pixel;
	}

	if (par->vbe_modes_cnt > 0)
		return 0;
	else
		return -EINVAL;
}