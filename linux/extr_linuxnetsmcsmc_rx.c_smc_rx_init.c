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
struct TYPE_4__ {int /*<<< orphan*/  urg_state; int /*<<< orphan*/  splice_pending; } ;
struct TYPE_3__ {int /*<<< orphan*/  sk_data_ready; } ;
struct smc_sock {TYPE_2__ conn; TYPE_1__ sk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_URG_READ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_rx_wake_up ; 

void smc_rx_init(struct smc_sock *smc)
{
	smc->sk.sk_data_ready = smc_rx_wake_up;
	atomic_set(&smc->conn.splice_pending, 0);
	smc->conn.urg_state = SMC_URG_READ;
}