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
struct net_device {struct ctcm_priv* ml_priv; } ;
struct mpc_group {int /*<<< orphan*/  fsm; } ;
struct ctcm_priv {struct mpc_group* mpcg; } ;
struct channel {struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  MPCG_EVENT_XID0DO ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct channel*) ; 

__attribute__((used)) static void ctcmpc_chx_resend(fsm_instance *fsm, int event, void *arg)
{
	struct channel	   *ch	   = arg;
	struct net_device  *dev    = ch->netdev;
	struct ctcm_priv   *priv   = dev->ml_priv;
	struct mpc_group   *grp    = priv->mpcg;

	fsm_event(grp->fsm, MPCG_EVENT_XID0DO, ch);
	return;
}