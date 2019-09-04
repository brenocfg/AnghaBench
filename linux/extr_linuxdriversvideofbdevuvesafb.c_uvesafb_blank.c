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
struct TYPE_3__ {int eax; int ebx; } ;
struct TYPE_4__ {TYPE_1__ regs; } ;
struct uvesafb_ktask {TYPE_2__ t; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
#define  FB_BLANK_NORMAL 130 
#define  FB_BLANK_POWERDOWN 129 
#define  FB_BLANK_UNBLANK 128 
 int uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_free (struct uvesafb_ktask*) ; 
 struct uvesafb_ktask* uvesafb_prep () ; 

__attribute__((used)) static int uvesafb_blank(int blank, struct fb_info *info)
{
	struct uvesafb_ktask *task;
	int err = 1;
#ifdef CONFIG_X86
	struct uvesafb_par *par = info->par;

	if (par->vbe_ib.capabilities & VBE_CAP_VGACOMPAT) {
		int loop = 10000;
		u8 seq = 0, crtc17 = 0;

		if (blank == FB_BLANK_POWERDOWN) {
			seq = 0x20;
			crtc17 = 0x00;
			err = 0;
		} else {
			seq = 0x00;
			crtc17 = 0x80;
			err = (blank == FB_BLANK_UNBLANK) ? 0 : -EINVAL;
		}

		vga_wseq(NULL, 0x00, 0x01);
		seq |= vga_rseq(NULL, 0x01) & ~0x20;
		vga_wseq(NULL, 0x00, seq);

		crtc17 |= vga_rcrt(NULL, 0x17) & ~0x80;
		while (loop--);
		vga_wcrt(NULL, 0x17, crtc17);
		vga_wseq(NULL, 0x00, 0x03);
	} else
#endif /* CONFIG_X86 */
	{
		task = uvesafb_prep();
		if (!task)
			return -ENOMEM;

		task->t.regs.eax = 0x4f10;
		switch (blank) {
		case FB_BLANK_UNBLANK:
			task->t.regs.ebx = 0x0001;
			break;
		case FB_BLANK_NORMAL:
			task->t.regs.ebx = 0x0101;	/* standby */
			break;
		case FB_BLANK_POWERDOWN:
			task->t.regs.ebx = 0x0401;	/* powerdown */
			break;
		default:
			goto out;
		}

		err = uvesafb_exec(task);
		if (err || (task->t.regs.eax & 0xffff) != 0x004f)
			err = 1;
out:		uvesafb_free(task);
	}
	return err;
}