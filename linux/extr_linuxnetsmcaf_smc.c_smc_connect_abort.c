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
struct smc_sock {TYPE_1__ conn; } ;

/* Variables and functions */
 int SMC_FIRST_CONTACT ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_conn_free (TYPE_1__*) ; 
 int /*<<< orphan*/  smc_create_lgr_pending ; 
 int /*<<< orphan*/  smc_lgr_forget (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smc_connect_abort(struct smc_sock *smc, int reason_code,
			     int local_contact)
{
	if (local_contact == SMC_FIRST_CONTACT)
		smc_lgr_forget(smc->conn.lgr);
	mutex_unlock(&smc_create_lgr_pending);
	smc_conn_free(&smc->conn);
	return reason_code;
}