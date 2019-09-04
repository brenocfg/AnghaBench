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
struct soc_pcmcia_socket {scalar_t__ nr; TYPE_1__* stat; } ;
struct TYPE_2__ {char* name; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_E740_PCMCIA_CD0 ; 
 int /*<<< orphan*/  GPIO_E740_PCMCIA_CD1 ; 
 int /*<<< orphan*/  GPIO_E740_PCMCIA_RDY0 ; 
 int /*<<< orphan*/  GPIO_E740_PCMCIA_RDY1 ; 
 size_t SOC_STAT_CD ; 
 size_t SOC_STAT_RDY ; 

__attribute__((used)) static int e740_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	if (skt->nr == 0) {
		skt->stat[SOC_STAT_CD].gpio = GPIO_E740_PCMCIA_CD0;
		skt->stat[SOC_STAT_CD].name = "CF card detect";
		skt->stat[SOC_STAT_RDY].gpio = GPIO_E740_PCMCIA_RDY0;
		skt->stat[SOC_STAT_RDY].name = "CF ready";
	} else {
		skt->stat[SOC_STAT_CD].gpio = GPIO_E740_PCMCIA_CD1;
		skt->stat[SOC_STAT_CD].name = "Wifi switch";
		skt->stat[SOC_STAT_RDY].gpio = GPIO_E740_PCMCIA_RDY1;
		skt->stat[SOC_STAT_RDY].name = "Wifi ready";
	}

	return 0;
}