#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct vbe_mode_ib {int mode_id; int bits_per_pixel; int /*<<< orphan*/  bytes_per_scan_line; } ;
struct vbe_crtc_ib {int horiz_start; int horiz_end; int horiz_total; int vert_start; int vert_end; int vert_total; int pixel_clock; int flags; scalar_t__ refresh_rate; } ;
struct TYPE_13__ {int vbe_version; int capabilities; } ;
struct uvesafb_par {int mode_idx; TYPE_5__ vbe_ib; int /*<<< orphan*/  crtc; int /*<<< orphan*/  nocrtc; struct vbe_mode_ib* vbe_modes; } ;
struct TYPE_14__ {int eax; int ebx; } ;
struct TYPE_16__ {int buf_len; TYPE_6__ regs; int /*<<< orphan*/  flags; } ;
struct uvesafb_ktask {TYPE_8__ t; int /*<<< orphan*/ * buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  line_length; int /*<<< orphan*/  visual; } ;
struct TYPE_12__ {int length; } ;
struct TYPE_11__ {int length; } ;
struct TYPE_10__ {int length; } ;
struct TYPE_15__ {int bits_per_pixel; int xres; int yres; scalar_t__ pixclock; int right_margin; int hsync_len; int left_margin; int lower_margin; int vsync_len; int upper_margin; int vmode; int sync; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct fb_info {TYPE_1__ fix; TYPE_7__ var; struct uvesafb_par* par; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int FB_SYNC_HOR_HIGH_ACT ; 
 int FB_SYNC_VERT_HIGH_ACT ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int /*<<< orphan*/  FB_VISUAL_TRUECOLOR ; 
 int FB_VMODE_DOUBLE ; 
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PICOS2KHZ (scalar_t__) ; 
 int /*<<< orphan*/  TF_BUF_ESDI ; 
 int UVESAFB_EXACT_DEPTH ; 
 int UVESAFB_EXACT_RES ; 
 int VBE_CAP_CAN_SWITCH_DAC ; 
 int dac_width ; 
 int /*<<< orphan*/  kfree (struct vbe_crtc_ib*) ; 
 struct vbe_crtc_ib* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct vbe_crtc_ib*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int) ; 
 int uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_free (struct uvesafb_ktask*) ; 
 struct uvesafb_ktask* uvesafb_prep () ; 
 int /*<<< orphan*/  uvesafb_reset (struct uvesafb_ktask*) ; 
 int uvesafb_vbe_find_mode (struct uvesafb_par*,int,int,int,int) ; 

__attribute__((used)) static int uvesafb_set_par(struct fb_info *info)
{
	struct uvesafb_par *par = info->par;
	struct uvesafb_ktask *task = NULL;
	struct vbe_crtc_ib *crtc = NULL;
	struct vbe_mode_ib *mode = NULL;
	int i, err = 0, depth = info->var.bits_per_pixel;

	if (depth > 8 && depth != 32)
		depth = info->var.red.length + info->var.green.length +
			info->var.blue.length;

	i = uvesafb_vbe_find_mode(par, info->var.xres, info->var.yres, depth,
				 UVESAFB_EXACT_RES | UVESAFB_EXACT_DEPTH);
	if (i >= 0)
		mode = &par->vbe_modes[i];
	else
		return -EINVAL;

	task = uvesafb_prep();
	if (!task)
		return -ENOMEM;
setmode:
	task->t.regs.eax = 0x4f02;
	task->t.regs.ebx = mode->mode_id | 0x4000;	/* use LFB */

	if (par->vbe_ib.vbe_version >= 0x0300 && !par->nocrtc &&
	    info->var.pixclock != 0) {
		task->t.regs.ebx |= 0x0800;		/* use CRTC data */
		task->t.flags = TF_BUF_ESDI;
		crtc = kzalloc(sizeof(struct vbe_crtc_ib), GFP_KERNEL);
		if (!crtc) {
			err = -ENOMEM;
			goto out;
		}
		crtc->horiz_start = info->var.xres + info->var.right_margin;
		crtc->horiz_end	  = crtc->horiz_start + info->var.hsync_len;
		crtc->horiz_total = crtc->horiz_end + info->var.left_margin;

		crtc->vert_start  = info->var.yres + info->var.lower_margin;
		crtc->vert_end    = crtc->vert_start + info->var.vsync_len;
		crtc->vert_total  = crtc->vert_end + info->var.upper_margin;

		crtc->pixel_clock = PICOS2KHZ(info->var.pixclock) * 1000;
		crtc->refresh_rate = (u16)(100 * (crtc->pixel_clock /
				(crtc->vert_total * crtc->horiz_total)));

		if (info->var.vmode & FB_VMODE_DOUBLE)
			crtc->flags |= 0x1;
		if (info->var.vmode & FB_VMODE_INTERLACED)
			crtc->flags |= 0x2;
		if (!(info->var.sync & FB_SYNC_HOR_HIGH_ACT))
			crtc->flags |= 0x4;
		if (!(info->var.sync & FB_SYNC_VERT_HIGH_ACT))
			crtc->flags |= 0x8;
		memcpy(&par->crtc, crtc, sizeof(*crtc));
	} else {
		memset(&par->crtc, 0, sizeof(*crtc));
	}

	task->t.buf_len = sizeof(struct vbe_crtc_ib);
	task->buf = &par->crtc;

	err = uvesafb_exec(task);
	if (err || (task->t.regs.eax & 0xffff) != 0x004f) {
		/*
		 * The mode switch might have failed because we tried to
		 * use our own timings.  Try again with the default timings.
		 */
		if (crtc != NULL) {
			pr_warn("mode switch failed (eax=0x%x, err=%d) - trying again with default timings\n",
				task->t.regs.eax, err);
			uvesafb_reset(task);
			kfree(crtc);
			crtc = NULL;
			info->var.pixclock = 0;
			goto setmode;
		} else {
			pr_err("mode switch failed (eax=0x%x, err=%d)\n",
			       task->t.regs.eax, err);
			err = -EINVAL;
			goto out;
		}
	}
	par->mode_idx = i;

	/* For 8bpp modes, always try to set the DAC to 8 bits. */
	if (par->vbe_ib.capabilities & VBE_CAP_CAN_SWITCH_DAC &&
	    mode->bits_per_pixel <= 8) {
		uvesafb_reset(task);
		task->t.regs.eax = 0x4f08;
		task->t.regs.ebx = 0x0800;

		err = uvesafb_exec(task);
		if (err || (task->t.regs.eax & 0xffff) != 0x004f ||
		    ((task->t.regs.ebx & 0xff00) >> 8) != 8) {
			dac_width = 6;
		} else {
			dac_width = 8;
		}
	}

	info->fix.visual = (info->var.bits_per_pixel == 8) ?
				FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_TRUECOLOR;
	info->fix.line_length = mode->bytes_per_scan_line;

out:
	kfree(crtc);
	uvesafb_free(task);

	return err;
}