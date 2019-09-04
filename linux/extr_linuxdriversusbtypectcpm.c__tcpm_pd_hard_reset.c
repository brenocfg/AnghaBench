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
struct tcpm_port {scalar_t__ hard_reset_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_RECOVERY ; 
 int /*<<< orphan*/  HARD_RESET_START ; 
 scalar_t__ PD_N_HARD_RESET_COUNT ; 
 int /*<<< orphan*/  tcpm_log_force (struct tcpm_port*,char*) ; 
 int /*<<< orphan*/  tcpm_set_state (struct tcpm_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _tcpm_pd_hard_reset(struct tcpm_port *port)
{
	tcpm_log_force(port, "Received hard reset");
	/*
	 * If we keep receiving hard reset requests, executing the hard reset
	 * must have failed. Revert to error recovery if that happens.
	 */
	tcpm_set_state(port,
		       port->hard_reset_count < PD_N_HARD_RESET_COUNT ?
				HARD_RESET_START : ERROR_RECOVERY,
		       0);
}