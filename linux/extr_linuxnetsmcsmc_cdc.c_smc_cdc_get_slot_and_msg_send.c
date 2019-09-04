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
struct smc_connection {int /*<<< orphan*/  send_lock; TYPE_1__* lgr; } ;
struct TYPE_2__ {scalar_t__ is_smcd; } ;

/* Variables and functions */
 int smcd_cdc_msg_send (struct smc_connection*) ; 
 int smcr_cdc_get_slot_and_msg_send (struct smc_connection*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int smc_cdc_get_slot_and_msg_send(struct smc_connection *conn)
{
	int rc;

	if (conn->lgr->is_smcd) {
		spin_lock_bh(&conn->send_lock);
		rc = smcd_cdc_msg_send(conn);
		spin_unlock_bh(&conn->send_lock);
	} else {
		rc = smcr_cdc_get_slot_and_msg_send(conn);
	}

	return rc;
}