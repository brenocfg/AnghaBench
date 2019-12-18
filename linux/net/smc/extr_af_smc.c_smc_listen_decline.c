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
struct TYPE_2__ {int /*<<< orphan*/  lgr; } ;
struct smc_sock {int fallback_rsn; TYPE_1__ conn; } ;

/* Variables and functions */
 int SMC_CLC_DECL_PEERDECL ; 
 int SMC_FIRST_CONTACT ; 
 scalar_t__ smc_clc_send_decline (struct smc_sock*,int) ; 
 int /*<<< orphan*/  smc_conn_free (TYPE_1__*) ; 
 int /*<<< orphan*/  smc_lgr_forget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_listen_out_connected (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_listen_out_err (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_switch_to_fallback (struct smc_sock*) ; 

__attribute__((used)) static void smc_listen_decline(struct smc_sock *new_smc, int reason_code,
			       int local_contact)
{
	/* RDMA setup failed, switch back to TCP */
	if (local_contact == SMC_FIRST_CONTACT)
		smc_lgr_forget(new_smc->conn.lgr);
	if (reason_code < 0) { /* error, no fallback possible */
		smc_listen_out_err(new_smc);
		return;
	}
	smc_conn_free(&new_smc->conn);
	smc_switch_to_fallback(new_smc);
	new_smc->fallback_rsn = reason_code;
	if (reason_code && reason_code != SMC_CLC_DECL_PEERDECL) {
		if (smc_clc_send_decline(new_smc, reason_code) < 0) {
			smc_listen_out_err(new_smc);
			return;
		}
	}
	smc_listen_out_connected(new_smc);
}