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
struct vhost_scsi_tpg {int /*<<< orphan*/  tv_tpg_mutex; struct vhost_scsi_nexus* tpg_nexus; int /*<<< orphan*/  se_tpg; } ;
struct vhost_scsi_nexus {int /*<<< orphan*/  tvn_se_sess; } ;
struct vhost_scsi_cmd {int dummy; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int TARGET_PROT_DIN_PASS ; 
 int TARGET_PROT_DOUT_PASS ; 
 int /*<<< orphan*/  VHOST_SCSI_DEFAULT_TAGS ; 
 int /*<<< orphan*/  kfree (struct vhost_scsi_nexus*) ; 
 struct vhost_scsi_nexus* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  target_setup_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,unsigned char*,struct vhost_scsi_nexus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_scsi_nexus_cb ; 

__attribute__((used)) static int vhost_scsi_make_nexus(struct vhost_scsi_tpg *tpg,
				const char *name)
{
	struct vhost_scsi_nexus *tv_nexus;

	mutex_lock(&tpg->tv_tpg_mutex);
	if (tpg->tpg_nexus) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_debug("tpg->tpg_nexus already exists\n");
		return -EEXIST;
	}

	tv_nexus = kzalloc(sizeof(*tv_nexus), GFP_KERNEL);
	if (!tv_nexus) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		pr_err("Unable to allocate struct vhost_scsi_nexus\n");
		return -ENOMEM;
	}
	/*
	 * Since we are running in 'demo mode' this call with generate a
	 * struct se_node_acl for the vhost_scsi struct se_portal_group with
	 * the SCSI Initiator port name of the passed configfs group 'name'.
	 */
	tv_nexus->tvn_se_sess = target_setup_session(&tpg->se_tpg,
					VHOST_SCSI_DEFAULT_TAGS,
					sizeof(struct vhost_scsi_cmd),
					TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS,
					(unsigned char *)name, tv_nexus,
					vhost_scsi_nexus_cb);
	if (IS_ERR(tv_nexus->tvn_se_sess)) {
		mutex_unlock(&tpg->tv_tpg_mutex);
		kfree(tv_nexus);
		return -ENOMEM;
	}
	tpg->tpg_nexus = tv_nexus;

	mutex_unlock(&tpg->tv_tpg_mutex);
	return 0;
}