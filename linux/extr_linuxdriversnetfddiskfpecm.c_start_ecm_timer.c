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
struct TYPE_2__ {int /*<<< orphan*/  ecm_timer; } ;
struct s_smc {TYPE_1__ e; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ECM ; 
 int /*<<< orphan*/  EV_TOKEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smt_timer_start (struct s_smc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_ecm_timer(struct s_smc *smc, u_long value, int event)
{
	smt_timer_start(smc,&smc->e.ecm_timer,value,EV_TOKEN(EVENT_ECM,event));
}