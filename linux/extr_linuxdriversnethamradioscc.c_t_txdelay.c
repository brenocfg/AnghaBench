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
struct timer_list {int dummy; } ;
struct scc_channel {int /*<<< orphan*/  irq; int /*<<< orphan*/ * tx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 struct scc_channel* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct scc_channel* scc ; 
 int /*<<< orphan*/  scc_start_maxkeyup (struct scc_channel*) ; 
 int /*<<< orphan*/  scc_txint (struct scc_channel*) ; 
 int /*<<< orphan*/  tx_t ; 

__attribute__((used)) static void t_txdelay(struct timer_list *t)
{
	struct scc_channel *scc = from_timer(scc, t, tx_t);

	scc_start_maxkeyup(scc);

	if (scc->tx_buff == NULL)
	{
		disable_irq(scc->irq);
		scc_txint(scc);	
		enable_irq(scc->irq);
	}
}