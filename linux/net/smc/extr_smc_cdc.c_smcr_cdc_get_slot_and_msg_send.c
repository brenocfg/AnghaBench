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
struct smc_wr_buf {int dummy; } ;
struct smc_connection {int /*<<< orphan*/  send_lock; } ;
struct smc_cdc_tx_pend {int dummy; } ;

/* Variables and functions */
 int smc_cdc_get_free_slot (struct smc_connection*,struct smc_wr_buf**,int /*<<< orphan*/ *,struct smc_cdc_tx_pend**) ; 
 int smc_cdc_msg_send (struct smc_connection*,struct smc_wr_buf*,struct smc_cdc_tx_pend*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smcr_cdc_get_slot_and_msg_send(struct smc_connection *conn)
{
	struct smc_cdc_tx_pend *pend;
	struct smc_wr_buf *wr_buf;
	int rc;

	rc = smc_cdc_get_free_slot(conn, &wr_buf, NULL, &pend);
	if (rc)
		return rc;

	spin_lock_bh(&conn->send_lock);
	rc = smc_cdc_msg_send(conn, wr_buf, pend);
	spin_unlock_bh(&conn->send_lock);
	return rc;
}