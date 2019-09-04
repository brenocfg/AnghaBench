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
struct nvidia_par {int dummy; } ;
struct fb_info {struct nvidia_par* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int NVReadCrtc (struct nvidia_par*,int) ; 
 int NVReadSeq (struct nvidia_par*,int) ; 
 int /*<<< orphan*/  NVTRACE_ENTER () ; 
 int /*<<< orphan*/  NVTRACE_LEAVE () ; 
 int /*<<< orphan*/  NVWriteCrtc (struct nvidia_par*,int,unsigned char) ; 
 int /*<<< orphan*/  NVWriteSeq (struct nvidia_par*,int,unsigned char) ; 

__attribute__((used)) static int nvidiafb_blank(int blank, struct fb_info *info)
{
	struct nvidia_par *par = info->par;
	unsigned char tmp, vesa;

	tmp = NVReadSeq(par, 0x01) & ~0x20;	/* screen on/off */
	vesa = NVReadCrtc(par, 0x1a) & ~0xc0;	/* sync on/off */

	NVTRACE_ENTER();

	if (blank)
		tmp |= 0x20;

	switch (blank) {
	case FB_BLANK_UNBLANK:
	case FB_BLANK_NORMAL:
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		vesa |= 0x80;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		vesa |= 0x40;
		break;
	case FB_BLANK_POWERDOWN:
		vesa |= 0xc0;
		break;
	}

	NVWriteSeq(par, 0x01, tmp);
	NVWriteCrtc(par, 0x1a, vesa);

	NVTRACE_LEAVE();

	return 0;
}