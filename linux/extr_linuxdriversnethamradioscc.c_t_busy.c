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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_state; int /*<<< orphan*/  txerrs; } ;
struct scc_channel {int /*<<< orphan*/  dev; TYPE_1__ stat; int /*<<< orphan*/  tx_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXS_IDLE ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct scc_channel* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 struct scc_channel* scc ; 
 int /*<<< orphan*/  scc_discard_buffers (struct scc_channel*) ; 
 int /*<<< orphan*/  tx_wdog ; 

__attribute__((used)) static void t_busy(struct timer_list *t)
{
	struct scc_channel *scc = from_timer(scc, t, tx_wdog);

	del_timer(&scc->tx_t);
	netif_stop_queue(scc->dev);	/* don't pile on the wabbit! */

	scc_discard_buffers(scc);
	scc->stat.txerrs++;
	scc->stat.tx_state = TXS_IDLE;

	netif_wake_queue(scc->dev);	
}