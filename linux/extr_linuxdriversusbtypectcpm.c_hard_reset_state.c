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
struct tcpm_port {scalar_t__ hard_reset_count; scalar_t__ pwr_role; scalar_t__ state; scalar_t__ pd_capable; } ;
typedef  enum tcpm_state { ____Placeholder_tcpm_state } tcpm_state ;

/* Variables and functions */
 int ERROR_RECOVERY ; 
 int HARD_RESET_SEND ; 
 scalar_t__ PD_N_HARD_RESET_COUNT ; 
 int SNK_READY ; 
 int SNK_UNATTACHED ; 
 scalar_t__ SNK_WAIT_CAPABILITIES ; 
 int SRC_UNATTACHED ; 
 scalar_t__ TYPEC_SOURCE ; 

__attribute__((used)) static inline enum tcpm_state hard_reset_state(struct tcpm_port *port)
{
	if (port->hard_reset_count < PD_N_HARD_RESET_COUNT)
		return HARD_RESET_SEND;
	if (port->pd_capable)
		return ERROR_RECOVERY;
	if (port->pwr_role == TYPEC_SOURCE)
		return SRC_UNATTACHED;
	if (port->state == SNK_WAIT_CAPABILITIES)
		return SNK_READY;
	return SNK_UNATTACHED;
}