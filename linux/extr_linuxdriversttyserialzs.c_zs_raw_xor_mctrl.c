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
typedef  int u8 ;
struct zs_port {int* regs; unsigned int mctrl; TYPE_1__* scc; } ;
struct TYPE_2__ {struct zs_port* zport; } ;

/* Variables and functions */
 int CTSIE ; 
 int DCDIE ; 
 int SYNCIE ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RNG ; 
 size_t ZS_CHAN_A ; 
 unsigned int zs_raw_get_ab_mctrl (struct zs_port*,struct zs_port*) ; 

__attribute__((used)) static unsigned int zs_raw_xor_mctrl(struct zs_port *zport)
{
	struct zs_port *zport_a = &zport->scc->zport[ZS_CHAN_A];
	unsigned int mmask, mctrl, delta;
	u8 mask_a, mask_b;

	if (zport == zport_a)
		return 0;

	mask_a = zport_a->regs[15];
	mask_b = zport->regs[15];

	mmask = ((mask_b & CTSIE) ? TIOCM_CTS : 0) |
		((mask_b & DCDIE) ? TIOCM_CAR : 0) |
		((mask_a & DCDIE) ? TIOCM_RNG : 0) |
		((mask_a & SYNCIE) ? TIOCM_DSR : 0);

	mctrl = zport->mctrl;
	if (mmask) {
		mctrl &= ~mmask;
		mctrl |= zs_raw_get_ab_mctrl(zport_a, zport) & mmask;
	}

	delta = mctrl ^ zport->mctrl;
	if (delta)
		zport->mctrl = mctrl;

	return delta;
}