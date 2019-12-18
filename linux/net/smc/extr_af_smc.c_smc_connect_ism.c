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
struct TYPE_4__ {scalar_t__ sk_state; } ;
struct smc_sock {TYPE_2__ sk; scalar_t__ connect_nonblock; } ;
struct smc_init_info {int is_smcd; int /*<<< orphan*/  cln_first_contact; int /*<<< orphan*/  srv_first_contact; int /*<<< orphan*/  ism_gid; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag; } ;
struct smc_clc_msg_accept_confirm {TYPE_1__ hdr; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 scalar_t__ SMC_ACTIVE ; 
 int SMC_CLC_DECL_MEM ; 
 scalar_t__ SMC_INIT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ smc_buf_create (struct smc_sock*,int) ; 
 int smc_clc_send_confirm (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_close_init (struct smc_sock*) ; 
 int smc_conn_create (struct smc_sock*,struct smc_init_info*) ; 
 int /*<<< orphan*/  smc_conn_save_peer_info (struct smc_sock*,struct smc_clc_msg_accept_confirm*) ; 
 int smc_connect_abort (struct smc_sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_copy_sock_settings_to_clc (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_rx_init (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_server_lgr_pending ; 
 int /*<<< orphan*/  smc_tx_init (struct smc_sock*) ; 

__attribute__((used)) static int smc_connect_ism(struct smc_sock *smc,
			   struct smc_clc_msg_accept_confirm *aclc,
			   struct smc_init_info *ini)
{
	int rc = 0;

	ini->is_smcd = true;
	ini->ism_gid = aclc->gid;
	ini->srv_first_contact = aclc->hdr.flag;

	/* there is only one lgr role for SMC-D; use server lock */
	mutex_lock(&smc_server_lgr_pending);
	rc = smc_conn_create(smc, ini);
	if (rc) {
		mutex_unlock(&smc_server_lgr_pending);
		return rc;
	}

	/* Create send and receive buffers */
	if (smc_buf_create(smc, true))
		return smc_connect_abort(smc, SMC_CLC_DECL_MEM,
					 ini->cln_first_contact);

	smc_conn_save_peer_info(smc, aclc);
	smc_close_init(smc);
	smc_rx_init(smc);
	smc_tx_init(smc);

	rc = smc_clc_send_confirm(smc);
	if (rc)
		return smc_connect_abort(smc, rc, ini->cln_first_contact);
	mutex_unlock(&smc_server_lgr_pending);

	smc_copy_sock_settings_to_clc(smc);
	smc->connect_nonblock = 0;
	if (smc->sk.sk_state == SMC_INIT)
		smc->sk.sk_state = SMC_ACTIVE;

	return 0;
}