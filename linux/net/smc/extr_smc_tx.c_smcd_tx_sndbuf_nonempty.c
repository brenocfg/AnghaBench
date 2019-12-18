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
struct smc_cdc_producer_flags {scalar_t__ urg_data_present; scalar_t__ urg_data_pending; } ;
struct TYPE_2__ {struct smc_cdc_producer_flags prod_flags; } ;
struct smc_connection {int /*<<< orphan*/  send_lock; TYPE_1__ local_tx_ctrl; } ;

/* Variables and functions */
 int smc_tx_rdma_writes (struct smc_connection*,int /*<<< orphan*/ *) ; 
 int smcd_cdc_msg_send (struct smc_connection*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smcd_tx_sndbuf_nonempty(struct smc_connection *conn)
{
	struct smc_cdc_producer_flags *pflags = &conn->local_tx_ctrl.prod_flags;
	int rc = 0;

	spin_lock_bh(&conn->send_lock);
	if (!pflags->urg_data_present)
		rc = smc_tx_rdma_writes(conn, NULL);
	if (!rc)
		rc = smcd_cdc_msg_send(conn);

	if (!rc && pflags->urg_data_present) {
		pflags->urg_data_pending = 0;
		pflags->urg_data_present = 0;
	}
	spin_unlock_bh(&conn->send_lock);
	return rc;
}