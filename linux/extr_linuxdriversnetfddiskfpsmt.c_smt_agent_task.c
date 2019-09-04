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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {int /*<<< orphan*/  smt_timer; } ;
struct s_smc {TYPE_1__ sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_SMT (char*) ; 
 int /*<<< orphan*/  EVENT_SMT ; 
 int /*<<< orphan*/  EV_TOKEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_TIMER ; 
 int /*<<< orphan*/  smt_timer_start (struct s_smc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void smt_agent_task(struct s_smc *smc)
{
	smt_timer_start(smc,&smc->sm.smt_timer, (u_long)1000000L,
		EV_TOKEN(EVENT_SMT,SM_TIMER)) ;
	DB_SMT("SMT agent task");
}