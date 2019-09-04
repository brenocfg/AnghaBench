#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  pci_irq; } ;
struct soc_pcmcia_socket {scalar_t__ nr; TYPE_2__* stat; TYPE_1__ socket; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAINSTONE_S0_CD_IRQ ; 
 int /*<<< orphan*/  MAINSTONE_S0_IRQ ; 
 int /*<<< orphan*/  MAINSTONE_S0_STSCHG_IRQ ; 
 int /*<<< orphan*/  MAINSTONE_S1_CD_IRQ ; 
 int /*<<< orphan*/  MAINSTONE_S1_IRQ ; 
 int /*<<< orphan*/  MAINSTONE_S1_STSCHG_IRQ ; 
 size_t SOC_STAT_BVD1 ; 
 size_t SOC_STAT_CD ; 

__attribute__((used)) static int mst_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	/*
	 * Setup default state of GPIO outputs
	 * before we enable them as outputs.
	 */
	if (skt->nr == 0) {
		skt->socket.pci_irq = MAINSTONE_S0_IRQ;
		skt->stat[SOC_STAT_CD].irq = MAINSTONE_S0_CD_IRQ;
		skt->stat[SOC_STAT_CD].name = "PCMCIA0 CD";
		skt->stat[SOC_STAT_BVD1].irq = MAINSTONE_S0_STSCHG_IRQ;
		skt->stat[SOC_STAT_BVD1].name = "PCMCIA0 STSCHG";
	} else {
		skt->socket.pci_irq = MAINSTONE_S1_IRQ;
		skt->stat[SOC_STAT_CD].irq = MAINSTONE_S1_CD_IRQ;
		skt->stat[SOC_STAT_CD].name = "PCMCIA1 CD";
		skt->stat[SOC_STAT_BVD1].irq = MAINSTONE_S1_STSCHG_IRQ;
		skt->stat[SOC_STAT_BVD1].name = "PCMCIA1 STSCHG";
	}
	return 0;
}