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
struct TYPE_2__ {double y_k; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 TYPE_1__ p_param ; 
 int /*<<< orphan*/  set_ctrl_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 
 double xk_1 ; 
 double xk_2 ; 

void controller_reset(void)
{
	/* TODO: relax control data when not over thermal limit */
	syslog(LOG_DEBUG, "TC inactive, relax p-state\n");
	p_param.y_k = 0.0;
	xk_1 = 0.0;
	xk_2 = 0.0;
	set_ctrl_state(0);
}