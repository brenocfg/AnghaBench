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
struct msdc_host {TYPE_1__* mrq; } ;
struct mmc_command {int /*<<< orphan*/  opcode; } ;
struct TYPE_2__ {struct mmc_command* stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TIMEOUT ; 
 int /*<<< orphan*/  ERR_MSG (char*,...) ; 
 int /*<<< orphan*/  msdc_clr_fifo (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_clr_int () ; 
 int /*<<< orphan*/  msdc_do_command (struct msdc_host*,struct mmc_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdc_reset_hw (struct msdc_host*) ; 

__attribute__((used)) static void msdc_abort_data(struct msdc_host *host)
{
	struct mmc_command *stop = host->mrq->stop;

	ERR_MSG("Need to Abort.");

	msdc_reset_hw(host);
	msdc_clr_fifo(host);
	msdc_clr_int();

	// need to check FIFO count 0 ?

	if (stop) {  /* try to stop, but may not success */
		ERR_MSG("stop when abort CMD<%d>", stop->opcode);
		(void)msdc_do_command(host, stop, 0, CMD_TIMEOUT);
	}

	//if (host->mclk >= 25000000) {
	//      msdc_set_mclk(host, 0, host->mclk >> 1);
	//}
}