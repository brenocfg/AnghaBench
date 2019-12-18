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
struct smcd_cdc_msg {int dummy; } ;
struct smc_host_cdc_msg {int dummy; } ;
struct smc_connection {TYPE_1__* lgr; } ;
struct smc_cdc_msg {int dummy; } ;
struct TYPE_2__ {scalar_t__ is_smcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  smcd_cdc_msg_to_host (struct smc_host_cdc_msg*,struct smcd_cdc_msg*,struct smc_connection*) ; 
 int /*<<< orphan*/  smcr_cdc_msg_to_host (struct smc_host_cdc_msg*,struct smc_cdc_msg*,struct smc_connection*) ; 

__attribute__((used)) static inline void smc_cdc_msg_to_host(struct smc_host_cdc_msg *local,
				       struct smc_cdc_msg *peer,
				       struct smc_connection *conn)
{
	if (conn->lgr->is_smcd)
		smcd_cdc_msg_to_host(local, (struct smcd_cdc_msg *)peer, conn);
	else
		smcr_cdc_msg_to_host(local, peer, conn);
}