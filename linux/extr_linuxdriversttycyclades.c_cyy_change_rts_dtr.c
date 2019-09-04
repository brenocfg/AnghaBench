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
typedef  int u32 ;
struct cyclades_port {int line; scalar_t__ rtsdtr_inv; struct cyclades_card* card; } ;
struct cyclades_card {int first_line; } ;

/* Variables and functions */
 int CyCAR ; 
 int CyDTR ; 
 int CyMSVR1 ; 
 int CyMSVR2 ; 
 int CyRTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  cyy_writeb (struct cyclades_port*,int,int) ; 

__attribute__((used)) static void cyy_change_rts_dtr(struct cyclades_port *info, unsigned int set,
		unsigned int clear)
{
	struct cyclades_card *card = info->card;
	int channel = info->line - card->first_line;
	u32 rts, dtr, msvrr, msvrd;

	channel &= 0x03;

	if (info->rtsdtr_inv) {
		msvrr = CyMSVR2;
		msvrd = CyMSVR1;
		rts = CyDTR;
		dtr = CyRTS;
	} else {
		msvrr = CyMSVR1;
		msvrd = CyMSVR2;
		rts = CyRTS;
		dtr = CyDTR;
	}
	if (set & TIOCM_RTS) {
		cyy_writeb(info, CyCAR, channel);
		cyy_writeb(info, msvrr, rts);
	}
	if (clear & TIOCM_RTS) {
		cyy_writeb(info, CyCAR, channel);
		cyy_writeb(info, msvrr, ~rts);
	}
	if (set & TIOCM_DTR) {
		cyy_writeb(info, CyCAR, channel);
		cyy_writeb(info, msvrd, dtr);
#ifdef CY_DEBUG_DTR
		printk(KERN_DEBUG "cyc:set_modem_info raising DTR\n");
		printk(KERN_DEBUG "     status: 0x%x, 0x%x\n",
			cyy_readb(info, CyMSVR1),
			cyy_readb(info, CyMSVR2));
#endif
	}
	if (clear & TIOCM_DTR) {
		cyy_writeb(info, CyCAR, channel);
		cyy_writeb(info, msvrd, ~dtr);
#ifdef CY_DEBUG_DTR
		printk(KERN_DEBUG "cyc:set_modem_info dropping DTR\n");
		printk(KERN_DEBUG "     status: 0x%x, 0x%x\n",
			cyy_readb(info, CyMSVR1),
			cyy_readb(info, CyMSVR2));
#endif
	}
}