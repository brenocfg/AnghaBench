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
struct smcd_cdc_msg {int dummy; } ;
struct TYPE_2__ {int peer_rmbe_idx; int peer_rmbe_size; int tx_off; int /*<<< orphan*/  peer_rmbe_space; int /*<<< orphan*/  peer_token; } ;
struct smc_sock {TYPE_1__ conn; } ;
struct smc_clc_msg_accept_confirm {int dmbe_idx; int /*<<< orphan*/  token; int /*<<< orphan*/  dmbe_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int smc_uncompress_bufsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smcd_conn_save_peer_info(struct smc_sock *smc,
				     struct smc_clc_msg_accept_confirm *clc)
{
	int bufsize = smc_uncompress_bufsize(clc->dmbe_size);

	smc->conn.peer_rmbe_idx = clc->dmbe_idx;
	smc->conn.peer_token = clc->token;
	/* msg header takes up space in the buffer */
	smc->conn.peer_rmbe_size = bufsize - sizeof(struct smcd_cdc_msg);
	atomic_set(&smc->conn.peer_rmbe_space, smc->conn.peer_rmbe_size);
	smc->conn.tx_off = bufsize * smc->conn.peer_rmbe_idx;
}