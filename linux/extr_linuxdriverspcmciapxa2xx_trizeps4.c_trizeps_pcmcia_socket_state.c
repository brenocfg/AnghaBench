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
struct soc_pcmcia_socket {size_t nr; } ;
struct pcmcia_state {int bvd1; int bvd2; int vs_3v; int vs_Xv; int /*<<< orphan*/  ready; int /*<<< orphan*/  detect; } ;

/* Variables and functions */
 unsigned short CFSR_readw () ; 
 unsigned short ConXS_CFSR_BVD1 ; 
 unsigned short ConXS_CFSR_BVD2 ; 
 unsigned short ConXS_CFSR_BVD_MASK ; 
 unsigned short ConXS_CFSR_VS1 ; 
 unsigned short ConXS_CFSR_VS2 ; 
 unsigned short* trizeps_pcmcia_status ; 

__attribute__((used)) static void trizeps_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
				struct pcmcia_state *state)
{
	unsigned short status = 0, change;
	status = CFSR_readw();
	change = (status ^ trizeps_pcmcia_status[skt->nr]) &
				ConXS_CFSR_BVD_MASK;
	if (change) {
		trizeps_pcmcia_status[skt->nr] = status;
		if (status & ConXS_CFSR_BVD1) {
			/* enable_irq empty */
		} else {
			/* disable_irq empty */
		}
	}

	switch (skt->nr) {
	case 0:
		/* just fill in fix states */
		state->bvd1   = (status & ConXS_CFSR_BVD1) ? 1 : 0;
		state->bvd2   = (status & ConXS_CFSR_BVD2) ? 1 : 0;
		state->vs_3v  = (status & ConXS_CFSR_VS1) ? 0 : 1;
		state->vs_Xv  = (status & ConXS_CFSR_VS2) ? 0 : 1;
		break;

#ifndef CONFIG_MACH_TRIZEPS_CONXS
	/* on ConXS we only have one slot. Second is inactive */
	case 1:
		state->detect = 0;
		state->ready  = 0;
		state->bvd1   = 0;
		state->bvd2   = 0;
		state->vs_3v  = 0;
		state->vs_Xv  = 0;
		break;

#endif
	}
}