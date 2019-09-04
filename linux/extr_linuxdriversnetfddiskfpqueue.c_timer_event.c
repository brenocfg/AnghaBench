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
typedef  int /*<<< orphan*/  u_long ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_T_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_T_EVENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINTF (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_event (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void timer_event(struct s_smc *smc, u_long token)
{
	PRINTF("timer event class %d token %d\n",
		EV_T_CLASS(token),
		EV_T_EVENT(token)) ;
	queue_event(smc,EV_T_CLASS(token),EV_T_EVENT(token));
}