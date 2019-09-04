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
struct TYPE_5__ {int height; int width; int /*<<< orphan*/  accel_flags; int /*<<< orphan*/  activate; scalar_t__ nonstd; } ;
struct TYPE_4__ {int ypanstep; int /*<<< orphan*/  accel; scalar_t__ ywrapstep; scalar_t__ xpanstep; scalar_t__ type_aux; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  cmap; int /*<<< orphan*/  pseudo_palette; int /*<<< orphan*/ * fbops; TYPE_2__ var; TYPE_1__ fix; } ;
struct cfb_info {unsigned int id; int ref_ps; int* divisors; TYPE_3__ fb; int /*<<< orphan*/  reg_b0_lock; int /*<<< orphan*/  pseudo_palette; } ;

/* Variables and functions */
 int FBINFO_DEFAULT ; 
 int FBINFO_HWACCEL_YPAN ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  FB_ACCEL_IGS_CYBER2000 ; 
 int /*<<< orphan*/  FB_ACCEL_IGS_CYBER2010 ; 
 int /*<<< orphan*/  FB_ACCEL_IGS_CYBER5000 ; 
 int /*<<< orphan*/  FB_ACTIVATE_NOW ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  ID_CYBERPRO_2000 131 
#define  ID_CYBERPRO_2010 130 
#define  ID_CYBERPRO_5000 129 
#define  ID_IGA_1682 128 
 int /*<<< orphan*/  NR_PALETTE ; 
 int /*<<< orphan*/  cyber2000fb_ops ; 
 int /*<<< orphan*/  fb_alloc_cmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cfb_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct cfb_info *cyberpro_alloc_fb_info(unsigned int id, char *name)
{
	struct cfb_info *cfb;

	cfb = kzalloc(sizeof(struct cfb_info), GFP_KERNEL);
	if (!cfb)
		return NULL;


	cfb->id			= id;

	if (id == ID_CYBERPRO_5000)
		cfb->ref_ps	= 40690; /* 24.576 MHz */
	else
		cfb->ref_ps	= 69842; /* 14.31818 MHz (69841?) */

	cfb->divisors[0]	= 1;
	cfb->divisors[1]	= 2;
	cfb->divisors[2]	= 4;

	if (id == ID_CYBERPRO_2000)
		cfb->divisors[3] = 8;
	else
		cfb->divisors[3] = 6;

	strcpy(cfb->fb.fix.id, name);

	cfb->fb.fix.type	= FB_TYPE_PACKED_PIXELS;
	cfb->fb.fix.type_aux	= 0;
	cfb->fb.fix.xpanstep	= 0;
	cfb->fb.fix.ypanstep	= 1;
	cfb->fb.fix.ywrapstep	= 0;

	switch (id) {
	case ID_IGA_1682:
		cfb->fb.fix.accel = 0;
		break;

	case ID_CYBERPRO_2000:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER2000;
		break;

	case ID_CYBERPRO_2010:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER2010;
		break;

	case ID_CYBERPRO_5000:
		cfb->fb.fix.accel = FB_ACCEL_IGS_CYBER5000;
		break;
	}

	cfb->fb.var.nonstd	= 0;
	cfb->fb.var.activate	= FB_ACTIVATE_NOW;
	cfb->fb.var.height	= -1;
	cfb->fb.var.width	= -1;
	cfb->fb.var.accel_flags	= FB_ACCELF_TEXT;

	cfb->fb.fbops		= &cyber2000fb_ops;
	cfb->fb.flags		= FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;
	cfb->fb.pseudo_palette	= cfb->pseudo_palette;

	spin_lock_init(&cfb->reg_b0_lock);

	fb_alloc_cmap(&cfb->fb.cmap, NR_PALETTE, 0);

	return cfb;
}