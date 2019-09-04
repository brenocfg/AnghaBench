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
struct soc_pcmcia_socket {int /*<<< orphan*/  clk; TYPE_2__* ops; TYPE_1__* stat; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hw_shutdown ) (struct soc_pcmcia_socket*) ;} ;
struct TYPE_3__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  stub1 (struct soc_pcmcia_socket*) ; 

__attribute__((used)) static void __soc_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt,
	unsigned int nr)
{
	unsigned int i;

	for (i = 0; i < nr; i++)
		if (skt->stat[i].irq)
			free_irq(skt->stat[i].irq, skt);

	if (skt->ops->hw_shutdown)
		skt->ops->hw_shutdown(skt);

	clk_disable_unprepare(skt->clk);
}