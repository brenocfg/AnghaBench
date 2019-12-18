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
struct mpoa_client {int dev_num; int /*<<< orphan*/  mps_ctrl_addr; int /*<<< orphan*/ * dev; struct atm_vcc* mpoad_vcc; } ;
struct lec_priv {int lane_version; TYPE_1__* lane2_ops; } ;
struct atm_vcc {int /*<<< orphan*/  flags; int /*<<< orphan*/ * dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  associate_indicator; } ;

/* Variables and functions */
 int ATM_ESA_LEN ; 
 int /*<<< orphan*/  ATM_VF_META ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int EADDRINUSE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct mpoa_client* alloc_mpc () ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/ * find_lec_by_itfnum (int) ; 
 struct mpoa_client* find_mpc_by_itfnum (int) ; 
 int /*<<< orphan*/  lane2_assoc_ind ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpc_dev ; 
 int /*<<< orphan*/  mpc_timer ; 
 int /*<<< orphan*/  mpc_timer_refresh () ; 
 int /*<<< orphan*/ * mpcs ; 
 int /*<<< orphan*/  mpoa_notifier ; 
 struct lec_priv* netdev_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int register_netdevice_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  send_set_mps_ctrl_addr (int /*<<< orphan*/ ,struct mpoa_client*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  start_mpc (struct mpoa_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcc_insert_socket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atm_mpoa_mpoad_attach(struct atm_vcc *vcc, int arg)
{
	struct mpoa_client *mpc;
	struct lec_priv *priv;
	int err;

	if (mpcs == NULL) {
		mpc_timer_refresh();

		/* This lets us now how our LECs are doing */
		err = register_netdevice_notifier(&mpoa_notifier);
		if (err < 0) {
			del_timer(&mpc_timer);
			return err;
		}
	}

	mpc = find_mpc_by_itfnum(arg);
	if (mpc == NULL) {
		dprintk("allocating new mpc for itf %d\n", arg);
		mpc = alloc_mpc();
		if (mpc == NULL)
			return -ENOMEM;
		mpc->dev_num = arg;
		mpc->dev = find_lec_by_itfnum(arg);
					/* NULL if there was no lec */
	}
	if (mpc->mpoad_vcc) {
		pr_info("mpoad is already present for itf %d\n", arg);
		return -EADDRINUSE;
	}

	if (mpc->dev) { /* check if the lec is LANE2 capable */
		priv = netdev_priv(mpc->dev);
		if (priv->lane_version < 2) {
			dev_put(mpc->dev);
			mpc->dev = NULL;
		} else
			priv->lane2_ops->associate_indicator = lane2_assoc_ind;
	}

	mpc->mpoad_vcc = vcc;
	vcc->dev = &mpc_dev;
	vcc_insert_socket(sk_atm(vcc));
	set_bit(ATM_VF_META, &vcc->flags);
	set_bit(ATM_VF_READY, &vcc->flags);

	if (mpc->dev) {
		char empty[ATM_ESA_LEN];
		memset(empty, 0, ATM_ESA_LEN);

		start_mpc(mpc, mpc->dev);
		/* set address if mpcd e.g. gets killed and restarted.
		 * If we do not do it now we have to wait for the next LE_ARP
		 */
		if (memcmp(mpc->mps_ctrl_addr, empty, ATM_ESA_LEN) != 0)
			send_set_mps_ctrl_addr(mpc->mps_ctrl_addr, mpc);
	}

	__module_get(THIS_MODULE);
	return arg;
}