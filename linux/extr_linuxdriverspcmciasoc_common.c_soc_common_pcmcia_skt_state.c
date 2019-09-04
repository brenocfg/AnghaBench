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
struct TYPE_6__ {int flags; scalar_t__ Vcc; } ;
struct soc_pcmcia_socket {TYPE_3__ cs_state; TYPE_2__* ops; TYPE_1__* stat; } ;
struct pcmcia_state {int bvd1; int bvd2; int detect; int ready; int vs_3v; int vs_Xv; scalar_t__ wrprot; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* socket_state ) (struct soc_pcmcia_socket*,struct pcmcia_state*) ;} ;
struct TYPE_4__ {scalar_t__ desc; } ;

/* Variables and functions */
 size_t SOC_STAT_BVD1 ; 
 size_t SOC_STAT_BVD2 ; 
 size_t SOC_STAT_CD ; 
 size_t SOC_STAT_RDY ; 
 size_t SOC_STAT_VS1 ; 
 size_t SOC_STAT_VS2 ; 
 unsigned int SS_3VCARD ; 
 unsigned int SS_BATDEAD ; 
 unsigned int SS_BATWARN ; 
 unsigned int SS_DETECT ; 
 int SS_IOCARD ; 
 unsigned int SS_POWERON ; 
 unsigned int SS_READY ; 
 unsigned int SS_STSCHG ; 
 unsigned int SS_WRPROT ; 
 unsigned int SS_XVCARD ; 
 int /*<<< orphan*/  gpiod_get_value (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct pcmcia_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct soc_pcmcia_socket*,struct pcmcia_state*) ; 

__attribute__((used)) static unsigned int soc_common_pcmcia_skt_state(struct soc_pcmcia_socket *skt)
{
	struct pcmcia_state state;
	unsigned int stat;

	memset(&state, 0, sizeof(struct pcmcia_state));

	/* Make battery voltage state report 'good' */
	state.bvd1 = 1;
	state.bvd2 = 1;

	if (skt->stat[SOC_STAT_CD].desc)
		state.detect = !!gpiod_get_value(skt->stat[SOC_STAT_CD].desc);
	if (skt->stat[SOC_STAT_RDY].desc)
		state.ready = !!gpiod_get_value(skt->stat[SOC_STAT_RDY].desc);
	if (skt->stat[SOC_STAT_BVD1].desc)
		state.bvd1 = !!gpiod_get_value(skt->stat[SOC_STAT_BVD1].desc);
	if (skt->stat[SOC_STAT_BVD2].desc)
		state.bvd2 = !!gpiod_get_value(skt->stat[SOC_STAT_BVD2].desc);
	if (skt->stat[SOC_STAT_VS1].desc)
		state.vs_3v = !!gpiod_get_value(skt->stat[SOC_STAT_VS1].desc);
	if (skt->stat[SOC_STAT_VS2].desc)
		state.vs_Xv = !!gpiod_get_value(skt->stat[SOC_STAT_VS2].desc);

	skt->ops->socket_state(skt, &state);

	stat = state.detect  ? SS_DETECT : 0;
	stat |= state.ready  ? SS_READY  : 0;
	stat |= state.wrprot ? SS_WRPROT : 0;
	stat |= state.vs_3v  ? SS_3VCARD : 0;
	stat |= state.vs_Xv  ? SS_XVCARD : 0;

	/* The power status of individual sockets is not available
	 * explicitly from the hardware, so we just remember the state
	 * and regurgitate it upon request:
	 */
	stat |= skt->cs_state.Vcc ? SS_POWERON : 0;

	if (skt->cs_state.flags & SS_IOCARD)
		stat |= state.bvd1 ? 0 : SS_STSCHG;
	else {
		if (state.bvd1 == 0)
			stat |= SS_BATDEAD;
		else if (state.bvd2 == 0)
			stat |= SS_BATWARN;
	}
	return stat;
}