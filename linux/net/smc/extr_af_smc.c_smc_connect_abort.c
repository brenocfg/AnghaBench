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
struct smc_sock {scalar_t__ connect_nonblock; TYPE_2__ conn; } ;
struct TYPE_3__ {scalar_t__ is_smcd; } ;

/* Variables and functions */
 int SMC_FIRST_CONTACT ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_client_lgr_pending ; 
 int /*<<< orphan*/  smc_conn_free (TYPE_2__*) ; 
 int /*<<< orphan*/  smc_lgr_forget (TYPE_1__*) ; 
 int /*<<< orphan*/  smc_server_lgr_pending ; 

__attribute__((used)) static int smc_connect_abort(struct smc_sock *smc, int reason_code,
			     int local_contact)
{
	if (local_contact == SMC_FIRST_CONTACT)
		smc_lgr_forget(smc->conn.lgr);
	if (smc->conn.lgr->is_smcd)
		/* there is only one lgr role for SMC-D; use server lock */
		mutex_unlock(&smc_server_lgr_pending);
	else
		mutex_unlock(&smc_client_lgr_pending);

	smc_conn_free(&smc->conn);
	smc->connect_nonblock = 0;
	return reason_code;
}