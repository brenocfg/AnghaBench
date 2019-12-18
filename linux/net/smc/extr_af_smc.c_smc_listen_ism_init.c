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
struct TYPE_4__ {TYPE_1__* lgr; } ;
struct smc_sock {TYPE_2__ conn; } ;
struct smc_init_info {scalar_t__ cln_first_contact; int /*<<< orphan*/  ism_gid; } ;
struct smc_clc_msg_smcd {int /*<<< orphan*/  gid; } ;
struct smc_clc_msg_proposal {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  smcd; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  peer_gid; } ;

/* Variables and functions */
 int SMC_CLC_DECL_MEM ; 
 int SMC_CLC_DECL_SMCDNOTALK ; 
 scalar_t__ SMC_FIRST_CONTACT ; 
 scalar_t__ smc_buf_create (struct smc_sock*,int) ; 
 int smc_conn_create (struct smc_sock*,struct smc_init_info*) ; 
 int /*<<< orphan*/  smc_conn_free (TYPE_2__*) ; 
 struct smc_clc_msg_smcd* smc_get_clc_msg_smcd (struct smc_clc_msg_proposal*) ; 
 scalar_t__ smc_ism_cantalk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smc_lgr_forget (TYPE_1__*) ; 

__attribute__((used)) static int smc_listen_ism_init(struct smc_sock *new_smc,
			       struct smc_clc_msg_proposal *pclc,
			       struct smc_init_info *ini)
{
	struct smc_clc_msg_smcd *pclc_smcd;
	int rc;

	pclc_smcd = smc_get_clc_msg_smcd(pclc);
	ini->ism_gid = pclc_smcd->gid;
	rc = smc_conn_create(new_smc, ini);
	if (rc)
		return rc;

	/* Check if peer can be reached via ISM device */
	if (smc_ism_cantalk(new_smc->conn.lgr->peer_gid,
			    new_smc->conn.lgr->vlan_id,
			    new_smc->conn.lgr->smcd)) {
		if (ini->cln_first_contact == SMC_FIRST_CONTACT)
			smc_lgr_forget(new_smc->conn.lgr);
		smc_conn_free(&new_smc->conn);
		return SMC_CLC_DECL_SMCDNOTALK;
	}

	/* Create send and receive buffers */
	if (smc_buf_create(new_smc, true)) {
		if (ini->cln_first_contact == SMC_FIRST_CONTACT)
			smc_lgr_forget(new_smc->conn.lgr);
		smc_conn_free(&new_smc->conn);
		return SMC_CLC_DECL_MEM;
	}

	return 0;
}