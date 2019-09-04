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
struct lynxfb_output {int paths; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_DISPLAY_CTRL ; 
 int CRT_DISPLAY_CTRL_BLANK ; 
 int CRT_DISPLAY_CTRL_DPMS_0 ; 
 int CRT_DISPLAY_CTRL_DPMS_1 ; 
 int CRT_DISPLAY_CTRL_DPMS_2 ; 
 int CRT_DISPLAY_CTRL_DPMS_3 ; 
 int CRT_DISPLAY_CTRL_DPMS_MASK ; 
 int EINVAL ; 
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int peek32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poke32 (int /*<<< orphan*/ ,unsigned int) ; 
 int sm750_crt ; 

int hw_sm750le_setBLANK(struct lynxfb_output *output, int blank)
{
	int dpms, crtdb;

	switch (blank) {
	case FB_BLANK_UNBLANK:
		dpms = CRT_DISPLAY_CTRL_DPMS_0;
		crtdb = 0;
		break;
	case FB_BLANK_NORMAL:
		dpms = CRT_DISPLAY_CTRL_DPMS_0;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		dpms = CRT_DISPLAY_CTRL_DPMS_2;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		dpms = CRT_DISPLAY_CTRL_DPMS_1;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	case FB_BLANK_POWERDOWN:
		dpms = CRT_DISPLAY_CTRL_DPMS_3;
		crtdb = CRT_DISPLAY_CTRL_BLANK;
		break;
	default:
		return -EINVAL;
	}

	if (output->paths & sm750_crt) {
		unsigned int val;

		val = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_DPMS_MASK;
		poke32(CRT_DISPLAY_CTRL, val | dpms);

		val = peek32(CRT_DISPLAY_CTRL) & ~CRT_DISPLAY_CTRL_BLANK;
		poke32(CRT_DISPLAY_CTRL, val | crtdb);
	}
	return 0;
}