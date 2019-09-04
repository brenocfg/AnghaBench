#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int smem_len; int line_length; int /*<<< orphan*/  accel; int /*<<< orphan*/  visual; int /*<<< orphan*/  type; scalar_t__* id; } ;
struct fb_info {TYPE_1__ fix; scalar_t__ par; } ;
struct cg6_par {int /*<<< orphan*/  fhc; } ;

/* Variables and functions */
#define  CG6_FHC_CPU_68020 129 
 int CG6_FHC_CPU_MASK ; 
#define  CG6_FHC_CPU_SPARC 128 
 int CG6_FHC_REV_MASK ; 
 int CG6_FHC_REV_SHIFT ; 
 int /*<<< orphan*/  FB_ACCEL_SUN_CGSIX ; 
 int /*<<< orphan*/  FB_TYPE_PACKED_PIXELS ; 
 int /*<<< orphan*/  FB_VISUAL_PSEUDOCOLOR ; 
 int sbus_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (scalar_t__*,char*,char const*,char const*) ; 

__attribute__((used)) static void cg6_init_fix(struct fb_info *info, int linebytes)
{
	struct cg6_par *par = (struct cg6_par *)info->par;
	const char *cg6_cpu_name, *cg6_card_name;
	u32 conf;

	conf = sbus_readl(par->fhc);
	switch (conf & CG6_FHC_CPU_MASK) {
	case CG6_FHC_CPU_SPARC:
		cg6_cpu_name = "sparc";
		break;
	case CG6_FHC_CPU_68020:
		cg6_cpu_name = "68020";
		break;
	default:
		cg6_cpu_name = "i386";
		break;
	}
	if (((conf >> CG6_FHC_REV_SHIFT) & CG6_FHC_REV_MASK) >= 11) {
		if (info->fix.smem_len <= 0x100000)
			cg6_card_name = "TGX";
		else
			cg6_card_name = "TGX+";
	} else {
		if (info->fix.smem_len <= 0x100000)
			cg6_card_name = "GX";
		else
			cg6_card_name = "GX+";
	}

	sprintf(info->fix.id, "%s %s", cg6_card_name, cg6_cpu_name);
	info->fix.id[sizeof(info->fix.id) - 1] = 0;

	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.visual = FB_VISUAL_PSEUDOCOLOR;

	info->fix.line_length = linebytes;

	info->fix.accel = FB_ACCEL_SUN_CGSIX;
}