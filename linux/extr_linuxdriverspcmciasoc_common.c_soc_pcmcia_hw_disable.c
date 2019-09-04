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
struct soc_pcmcia_socket {TYPE_1__* stat; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  irq_set_irq_type (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void soc_pcmcia_hw_disable(struct soc_pcmcia_socket *skt)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(skt->stat); i++)
		if (skt->stat[i].irq)
			irq_set_irq_type(skt->stat[i].irq, IRQ_TYPE_NONE);
}