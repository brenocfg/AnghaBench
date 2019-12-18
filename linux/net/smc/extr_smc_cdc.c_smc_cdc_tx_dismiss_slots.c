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
struct smc_link {int dummy; } ;
struct smc_connection {TYPE_1__* lgr; } ;
struct TYPE_2__ {struct smc_link* lnk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMC_CDC_MSG_TYPE ; 
 size_t SMC_SINGLE_LINK ; 
 int /*<<< orphan*/  smc_cdc_tx_dismisser ; 
 int /*<<< orphan*/  smc_cdc_tx_filter ; 
 int /*<<< orphan*/  smc_wr_tx_dismiss_slots (struct smc_link*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

void smc_cdc_tx_dismiss_slots(struct smc_connection *conn)
{
	struct smc_link *link = &conn->lgr->lnk[SMC_SINGLE_LINK];

	smc_wr_tx_dismiss_slots(link, SMC_CDC_MSG_TYPE,
				smc_cdc_tx_filter, smc_cdc_tx_dismisser,
				(unsigned long)conn);
}