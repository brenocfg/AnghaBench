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
struct smc_link_group {int /*<<< orphan*/  conns_num; scalar_t__ is_smcd; } ;
struct smc_connection {struct smc_link_group* lgr; int /*<<< orphan*/  rx_tsklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  smc_buf_unuse (struct smc_connection*,struct smc_link_group*) ; 
 int /*<<< orphan*/  smc_cdc_tx_dismiss_slots (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_ism_unset_conn (struct smc_connection*) ; 
 int /*<<< orphan*/  smc_lgr_schedule_free_work (struct smc_link_group*) ; 
 int /*<<< orphan*/  smc_lgr_unregister_conn (struct smc_connection*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

void smc_conn_free(struct smc_connection *conn)
{
	struct smc_link_group *lgr = conn->lgr;

	if (!lgr)
		return;
	if (lgr->is_smcd) {
		smc_ism_unset_conn(conn);
		tasklet_kill(&conn->rx_tsklet);
	} else {
		smc_cdc_tx_dismiss_slots(conn);
	}
	smc_lgr_unregister_conn(conn);
	smc_buf_unuse(conn, lgr);		/* allow buffer reuse */
	conn->lgr = NULL;

	if (!lgr->conns_num)
		smc_lgr_schedule_free_work(lgr);
}