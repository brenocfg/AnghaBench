#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct iscsi_tiqn {int tiqn_index; int /*<<< orphan*/  tiqn; int /*<<< orphan*/  tiqn_list; int /*<<< orphan*/  tiqn_state; TYPE_3__ logout_stats; TYPE_2__ login_stats; TYPE_1__ sess_err_stats; int /*<<< orphan*/  tiqn_tpg_lock; int /*<<< orphan*/  tiqn_state_lock; int /*<<< orphan*/  tiqn_tpg_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct iscsi_tiqn* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ ISCSI_IQN_LEN ; 
 int /*<<< orphan*/  TIQN_STATE_ACTIVE ; 
 int /*<<< orphan*/  g_tiqn_list ; 
 int idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  kfree (struct iscsi_tiqn*) ; 
 struct iscsi_tiqn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,unsigned char*) ; 
 scalar_t__ strlen (unsigned char*) ; 
 int /*<<< orphan*/  tiqn_idr ; 
 int /*<<< orphan*/  tiqn_lock ; 

struct iscsi_tiqn *iscsit_add_tiqn(unsigned char *buf)
{
	struct iscsi_tiqn *tiqn = NULL;
	int ret;

	if (strlen(buf) >= ISCSI_IQN_LEN) {
		pr_err("Target IQN exceeds %d bytes\n",
				ISCSI_IQN_LEN);
		return ERR_PTR(-EINVAL);
	}

	tiqn = kzalloc(sizeof(*tiqn), GFP_KERNEL);
	if (!tiqn)
		return ERR_PTR(-ENOMEM);

	sprintf(tiqn->tiqn, "%s", buf);
	INIT_LIST_HEAD(&tiqn->tiqn_list);
	INIT_LIST_HEAD(&tiqn->tiqn_tpg_list);
	spin_lock_init(&tiqn->tiqn_state_lock);
	spin_lock_init(&tiqn->tiqn_tpg_lock);
	spin_lock_init(&tiqn->sess_err_stats.lock);
	spin_lock_init(&tiqn->login_stats.lock);
	spin_lock_init(&tiqn->logout_stats.lock);

	tiqn->tiqn_state = TIQN_STATE_ACTIVE;

	idr_preload(GFP_KERNEL);
	spin_lock(&tiqn_lock);

	ret = idr_alloc(&tiqn_idr, NULL, 0, 0, GFP_NOWAIT);
	if (ret < 0) {
		pr_err("idr_alloc() failed for tiqn->tiqn_index\n");
		spin_unlock(&tiqn_lock);
		idr_preload_end();
		kfree(tiqn);
		return ERR_PTR(ret);
	}
	tiqn->tiqn_index = ret;
	list_add_tail(&tiqn->tiqn_list, &g_tiqn_list);

	spin_unlock(&tiqn_lock);
	idr_preload_end();

	pr_debug("CORE[0] - Added iSCSI Target IQN: %s\n", tiqn->tiqn);

	return tiqn;

}