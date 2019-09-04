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
struct smc_link_group {scalar_t__ role; int /*<<< orphan*/  is_smcd; int /*<<< orphan*/  free_work; } ;

/* Variables and functions */
 scalar_t__ SMC_CLNT ; 
 int /*<<< orphan*/  SMC_LGR_FREE_DELAY_CLNT ; 
 int /*<<< orphan*/  SMC_LGR_FREE_DELAY_SERV ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_wq ; 

__attribute__((used)) static void smc_lgr_schedule_free_work(struct smc_link_group *lgr)
{
	/* client link group creation always follows the server link group
	 * creation. For client use a somewhat higher removal delay time,
	 * otherwise there is a risk of out-of-sync link groups.
	 */
	mod_delayed_work(system_wq, &lgr->free_work,
			 (!lgr->is_smcd && lgr->role == SMC_CLNT) ?
			 SMC_LGR_FREE_DELAY_CLNT : SMC_LGR_FREE_DELAY_SERV);
}