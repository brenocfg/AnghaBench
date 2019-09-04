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
struct smcd_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ sk_state; } ;
struct smc_sock {TYPE_2__ sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  flag; } ;
struct smc_clc_msg_accept_confirm {int /*<<< orphan*/  gid; TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ SMC_ACTIVE ; 
 int SMC_CLC_DECL_MEM ; 
 int SMC_FIRST_CONTACT ; 
 scalar_t__ SMC_INIT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ smc_buf_create (struct smc_sock*,int) ; 
 int smc_clc_send_confirm (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_close_init (struct smc_sock*) ; 
 int smc_conn_create (struct smc_sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct smcd_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_conn_save_peer_info (struct smc_sock*,struct smc_clc_msg_accept_confirm*) ; 
 int smc_connect_abort (struct smc_sock*,int,int) ; 
 int /*<<< orphan*/  smc_copy_sock_settings_to_clc (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_create_lgr_pending ; 
 int /*<<< orphan*/  smc_rx_init (struct smc_sock*) ; 
 int /*<<< orphan*/  smc_tx_init (struct smc_sock*) ; 

__attribute__((used)) static int smc_connect_ism(struct smc_sock *smc,
			   struct smc_clc_msg_accept_confirm *aclc,
			   struct smcd_dev *ismdev)
{
	int local_contact = SMC_FIRST_CONTACT;
	int rc = 0;

	mutex_lock(&smc_create_lgr_pending);
	local_contact = smc_conn_create(smc, true, aclc->hdr.flag, NULL, 0,
					NULL, ismdev, aclc->gid);
	if (local_contact < 0)
		return smc_connect_abort(smc, SMC_CLC_DECL_MEM, 0);

	/* Create send and receive buffers */
	if (smc_buf_create(smc, true))
		return smc_connect_abort(smc, SMC_CLC_DECL_MEM, local_contact);

	smc_conn_save_peer_info(smc, aclc);
	smc_close_init(smc);
	smc_rx_init(smc);
	smc_tx_init(smc);

	rc = smc_clc_send_confirm(smc);
	if (rc)
		return smc_connect_abort(smc, rc, local_contact);
	mutex_unlock(&smc_create_lgr_pending);

	smc_copy_sock_settings_to_clc(smc);
	if (smc->sk.sk_state == SMC_INIT)
		smc->sk.sk_state = SMC_ACTIVE;

	return 0;
}