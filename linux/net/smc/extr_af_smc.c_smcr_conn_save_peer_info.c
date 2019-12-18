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
struct TYPE_3__ {int /*<<< orphan*/  token; } ;
struct TYPE_4__ {int peer_rmbe_idx; int peer_rmbe_size; int tx_off; int /*<<< orphan*/  peer_rmbe_space; TYPE_1__ local_tx_ctrl; } ;
struct smc_sock {TYPE_2__ conn; } ;
struct smc_clc_msg_accept_confirm {int rmbe_idx; int /*<<< orphan*/  rmbe_alert_token; int /*<<< orphan*/  rmbe_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int smc_uncompress_bufsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smcr_conn_save_peer_info(struct smc_sock *smc,
				     struct smc_clc_msg_accept_confirm *clc)
{
	int bufsize = smc_uncompress_bufsize(clc->rmbe_size);

	smc->conn.peer_rmbe_idx = clc->rmbe_idx;
	smc->conn.local_tx_ctrl.token = ntohl(clc->rmbe_alert_token);
	smc->conn.peer_rmbe_size = bufsize;
	atomic_set(&smc->conn.peer_rmbe_space, smc->conn.peer_rmbe_size);
	smc->conn.tx_off = bufsize * (smc->conn.peer_rmbe_idx - 1);
}