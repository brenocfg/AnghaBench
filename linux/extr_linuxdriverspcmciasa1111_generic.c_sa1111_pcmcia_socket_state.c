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
struct soc_pcmcia_socket {int nr; } ;
struct sa1111_pcmcia_socket {TYPE_1__* dev; } ;
struct pcmcia_state {int detect; int ready; int bvd1; int bvd2; int wrprot; int vs_3v; int vs_Xv; } ;
struct TYPE_2__ {scalar_t__ mapbase; } ;

/* Variables and functions */
 scalar_t__ PCSR ; 
 int PCSR_S0_BVD1 ; 
 int PCSR_S0_BVD2 ; 
 int PCSR_S0_DETECT ; 
 int PCSR_S0_READY ; 
 int PCSR_S0_VS1 ; 
 int PCSR_S0_VS2 ; 
 int PCSR_S0_WP ; 
 int PCSR_S1_BVD1 ; 
 int PCSR_S1_BVD2 ; 
 int PCSR_S1_DETECT ; 
 int PCSR_S1_READY ; 
 int PCSR_S1_VS1 ; 
 int PCSR_S1_VS2 ; 
 int PCSR_S1_WP ; 
 int readl_relaxed (scalar_t__) ; 
 struct sa1111_pcmcia_socket* to_skt (struct soc_pcmcia_socket*) ; 

void sa1111_pcmcia_socket_state(struct soc_pcmcia_socket *skt, struct pcmcia_state *state)
{
	struct sa1111_pcmcia_socket *s = to_skt(skt);
	u32 status = readl_relaxed(s->dev->mapbase + PCSR);

	switch (skt->nr) {
	case 0:
		state->detect = status & PCSR_S0_DETECT ? 0 : 1;
		state->ready  = status & PCSR_S0_READY  ? 1 : 0;
		state->bvd1   = status & PCSR_S0_BVD1   ? 1 : 0;
		state->bvd2   = status & PCSR_S0_BVD2   ? 1 : 0;
		state->wrprot = status & PCSR_S0_WP     ? 1 : 0;
		state->vs_3v  = status & PCSR_S0_VS1    ? 0 : 1;
		state->vs_Xv  = status & PCSR_S0_VS2    ? 0 : 1;
		break;

	case 1:
		state->detect = status & PCSR_S1_DETECT ? 0 : 1;
		state->ready  = status & PCSR_S1_READY  ? 1 : 0;
		state->bvd1   = status & PCSR_S1_BVD1   ? 1 : 0;
		state->bvd2   = status & PCSR_S1_BVD2   ? 1 : 0;
		state->wrprot = status & PCSR_S1_WP     ? 1 : 0;
		state->vs_3v  = status & PCSR_S1_VS1    ? 0 : 1;
		state->vs_Xv  = status & PCSR_S1_VS2    ? 0 : 1;
		break;
	}
}