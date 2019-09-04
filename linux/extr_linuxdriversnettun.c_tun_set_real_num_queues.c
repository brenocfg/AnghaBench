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
struct tun_struct {int /*<<< orphan*/  numqueues; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_set_real_num_rx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_set_real_num_queues(struct tun_struct *tun)
{
	netif_set_real_num_tx_queues(tun->dev, tun->numqueues);
	netif_set_real_num_rx_queues(tun->dev, tun->numqueues);
}