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
struct tridentfb_par {scalar_t__ flatpanel; } ;
struct fb_info {struct tridentfb_par* par; } ;

/* Variables and functions */
#define  FB_BLANK_HSYNC_SUSPEND 132 
#define  FB_BLANK_NORMAL 131 
#define  FB_BLANK_POWERDOWN 130 
#define  FB_BLANK_UNBLANK 129 
#define  FB_BLANK_VSYNC_SUSPEND 128 
 int /*<<< orphan*/  PowerStatus ; 
 int /*<<< orphan*/  debug (char*) ; 
 int read3CE (struct tridentfb_par*,int /*<<< orphan*/ ) ; 
 int t_inb (struct tridentfb_par*,int) ; 
 int /*<<< orphan*/  t_outb (struct tridentfb_par*,unsigned char,int) ; 
 int /*<<< orphan*/  write3CE (struct tridentfb_par*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int tridentfb_blank(int blank_mode, struct fb_info *info)
{
	unsigned char PMCont, DPMSCont;
	struct tridentfb_par *par = info->par;

	debug("enter\n");
	if (par->flatpanel)
		return 0;
	t_outb(par, 0x04, 0x83C8); /* Read DPMS Control */
	PMCont = t_inb(par, 0x83C6) & 0xFC;
	DPMSCont = read3CE(par, PowerStatus) & 0xFC;
	switch (blank_mode) {
	case FB_BLANK_UNBLANK:
		/* Screen: On, HSync: On, VSync: On */
	case FB_BLANK_NORMAL:
		/* Screen: Off, HSync: On, VSync: On */
		PMCont |= 0x03;
		DPMSCont |= 0x00;
		break;
	case FB_BLANK_HSYNC_SUSPEND:
		/* Screen: Off, HSync: Off, VSync: On */
		PMCont |= 0x02;
		DPMSCont |= 0x01;
		break;
	case FB_BLANK_VSYNC_SUSPEND:
		/* Screen: Off, HSync: On, VSync: Off */
		PMCont |= 0x02;
		DPMSCont |= 0x02;
		break;
	case FB_BLANK_POWERDOWN:
		/* Screen: Off, HSync: Off, VSync: Off */
		PMCont |= 0x00;
		DPMSCont |= 0x03;
		break;
	}

	write3CE(par, PowerStatus, DPMSCont);
	t_outb(par, 4, 0x83C8);
	t_outb(par, PMCont, 0x83C6);

	debug("exit\n");

	/* let fbcon do a softblank for us */
	return (blank_mode == FB_BLANK_NORMAL) ? 1 : 0;
}