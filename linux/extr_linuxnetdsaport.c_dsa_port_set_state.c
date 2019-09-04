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
typedef  scalar_t__ u8 ;
struct switchdev_trans {int dummy; } ;
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int index; scalar_t__ stp_state; struct dsa_switch* ds; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* port_fast_age ) (struct dsa_switch*,int) ;int /*<<< orphan*/  (* port_stp_state_set ) (struct dsa_switch*,int,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ BR_STATE_BLOCKING ; 
 scalar_t__ BR_STATE_DISABLED ; 
 scalar_t__ BR_STATE_FORWARDING ; 
 scalar_t__ BR_STATE_LEARNING ; 
 scalar_t__ BR_STATE_LISTENING ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*,int,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (struct dsa_switch*,int) ; 
 scalar_t__ switchdev_trans_ph_prepare (struct switchdev_trans*) ; 

int dsa_port_set_state(struct dsa_port *dp, u8 state,
		       struct switchdev_trans *trans)
{
	struct dsa_switch *ds = dp->ds;
	int port = dp->index;

	if (switchdev_trans_ph_prepare(trans))
		return ds->ops->port_stp_state_set ? 0 : -EOPNOTSUPP;

	if (ds->ops->port_stp_state_set)
		ds->ops->port_stp_state_set(ds, port, state);

	if (ds->ops->port_fast_age) {
		/* Fast age FDB entries or flush appropriate forwarding database
		 * for the given port, if we are moving it from Learning or
		 * Forwarding state, to Disabled or Blocking or Listening state.
		 */

		if ((dp->stp_state == BR_STATE_LEARNING ||
		     dp->stp_state == BR_STATE_FORWARDING) &&
		    (state == BR_STATE_DISABLED ||
		     state == BR_STATE_BLOCKING ||
		     state == BR_STATE_LISTENING))
			ds->ops->port_fast_age(ds, port);
	}

	dp->stp_state = state;

	return 0;
}