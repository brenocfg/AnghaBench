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
struct vscsibk_pend {int dummy; } ;
struct scsiback_tpg {int /*<<< orphan*/  tv_tpg_mutex; int /*<<< orphan*/  se_tpg; scalar_t__ tpg_nexus; } ;
struct scsiback_nexus {int /*<<< orphan*/  tvn_se_sess; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_PROT_NORMAL ; 
 int /*<<< orphan*/  VSCSI_DEFAULT_SESSION_TAGS ; 
 int /*<<< orphan*/  kfree (struct scsiback_nexus*) ; 
 struct scsiback_nexus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  scsiback_alloc_sess_cb ; 
 int /*<<< orphan*/  target_setup_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,struct scsiback_nexus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scsiback_make_nexus(struct scsiback_tpg *tpg,
				const char *name)
{
	struct scsiback_nexus *tv_nexus;
	int ret = 0;

	mutex_lock(&tpg->tv_tpg_mutex);
	if (tpg->tpg_nexus) {
		pr_debug("tpg->tpg_nexus already exists\n");
		ret = -EEXIST;
		goto out_unlock;
	}

	tv_nexus = kzalloc(sizeof(struct scsiback_nexus), GFP_KERNEL);
	if (!tv_nexus) {
		ret = -ENOMEM;
		goto out_unlock;
	}

	tv_nexus->tvn_se_sess = target_setup_session(&tpg->se_tpg,
						     VSCSI_DEFAULT_SESSION_TAGS,
						     sizeof(struct vscsibk_pend),
						     TARGET_PROT_NORMAL, name,
						     tv_nexus, scsiback_alloc_sess_cb);
	if (IS_ERR(tv_nexus->tvn_se_sess)) {
		kfree(tv_nexus);
		ret = -ENOMEM;
		goto out_unlock;
	}

out_unlock:
	mutex_unlock(&tpg->tv_tpg_mutex);
	return ret;
}