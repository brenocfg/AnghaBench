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
struct netcp_intf {int /*<<< orphan*/  tx_napi; int /*<<< orphan*/  tx_compl_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  knav_queue_disable_notify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netcp_tx_notify(void *arg)
{
	struct netcp_intf *netcp = arg;

	knav_queue_disable_notify(netcp->tx_compl_q);
	napi_schedule(&netcp->tx_napi);
}