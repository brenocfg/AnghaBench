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
struct smc_connection {TYPE_1__* lgr; } ;
struct TYPE_2__ {scalar_t__ is_smcd; } ;

/* Variables and functions */
 int smcd_tx_sndbuf_nonempty (struct smc_connection*) ; 
 int smcr_tx_sndbuf_nonempty (struct smc_connection*) ; 

int smc_tx_sndbuf_nonempty(struct smc_connection *conn)
{
	int rc;

	if (conn->lgr->is_smcd)
		rc = smcd_tx_sndbuf_nonempty(conn);
	else
		rc = smcr_tx_sndbuf_nonempty(conn);

	return rc;
}