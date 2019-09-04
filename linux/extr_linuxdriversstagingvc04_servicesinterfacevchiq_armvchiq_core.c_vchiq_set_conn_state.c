#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t conn_state; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ VCHIQ_STATE_T ;
typedef  size_t VCHIQ_CONNSTATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * conn_state_names ; 
 int /*<<< orphan*/  vchiq_core_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_platform_conn_state_changed (TYPE_1__*,size_t,size_t) ; 

inline void
vchiq_set_conn_state(VCHIQ_STATE_T *state, VCHIQ_CONNSTATE_T newstate)
{
	VCHIQ_CONNSTATE_T oldstate = state->conn_state;

	vchiq_log_info(vchiq_core_log_level, "%d: %s->%s", state->id,
		conn_state_names[oldstate],
		conn_state_names[newstate]);
	state->conn_state = newstate;
	vchiq_platform_conn_state_changed(state, oldstate, newstate);
}