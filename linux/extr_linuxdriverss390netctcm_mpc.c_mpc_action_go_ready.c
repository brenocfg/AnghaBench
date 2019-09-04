#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; struct ctcm_priv* ml_priv; } ;
struct mpc_group {int send_qllc_disc; int port_persist; int /*<<< orphan*/  mpc_tasklet2; scalar_t__ estconn_called; scalar_t__ out_of_sequence; int /*<<< orphan*/  fsm; scalar_t__ allochanfunc; int /*<<< orphan*/  (* estconnfunc ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  group_max_buflen; int /*<<< orphan*/  port_num; TYPE_1__* saved_xid2; int /*<<< orphan*/  timer; } ;
struct ctcm_priv {TYPE_2__* xid; struct mpc_group* mpcg; } ;
typedef  int /*<<< orphan*/  fsm_instance ;
struct TYPE_4__ {int xid2_flag2; } ;
struct TYPE_3__ {int xid2_flag2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 int /*<<< orphan*/  MPCG_EVENT_INOP ; 
 int /*<<< orphan*/  MPC_ERROR ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mpc_action_go_ready(fsm_instance *fsm, int event, void *arg)
{
	struct net_device *dev = arg;
	struct ctcm_priv *priv = dev->ml_priv;
	struct mpc_group *grp = priv->mpcg;

	if (grp == NULL) {
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
			"%s(%s): No MPC group",
				CTCM_FUNTAIL, dev->name);
		return;
	}

	fsm_deltimer(&grp->timer);

	if (grp->saved_xid2->xid2_flag2 == 0x40) {
		priv->xid->xid2_flag2 = 0x00;
		if (grp->estconnfunc) {
			grp->estconnfunc(grp->port_num, 1,
					grp->group_max_buflen);
			grp->estconnfunc = NULL;
		} else if (grp->allochanfunc)
			grp->send_qllc_disc = 1;

		fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
		CTCM_DBF_TEXT_(MPC_ERROR, CTC_DBF_ERROR,
				"%s(%s): fails",
					CTCM_FUNTAIL, dev->name);
		return;
	}

	grp->port_persist = 1;
	grp->out_of_sequence = 0;
	grp->estconn_called = 0;

	tasklet_hi_schedule(&grp->mpc_tasklet2);

	return;
}