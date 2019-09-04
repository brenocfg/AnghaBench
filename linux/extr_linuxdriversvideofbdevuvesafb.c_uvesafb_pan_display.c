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
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int uvesafb_pan_display(struct fb_var_screeninfo *var,
		struct fb_info *info)
{
#ifdef CONFIG_X86_32
	int offset;
	struct uvesafb_par *par = info->par;

	offset = (var->yoffset * info->fix.line_length + var->xoffset) / 4;

	/*
	 * It turns out it's not the best idea to do panning via vm86,
	 * so we only allow it if we have a PMI.
	 */
	if (par->pmi_start) {
		__asm__ __volatile__(
			"call *(%%edi)"
			: /* no return value */
			: "a" (0x4f07),         /* EAX */
			  "b" (0),              /* EBX */
			  "c" (offset),         /* ECX */
			  "d" (offset >> 16),   /* EDX */
			  "D" (&par->pmi_start));    /* EDI */
	}
#endif
	return 0;
}