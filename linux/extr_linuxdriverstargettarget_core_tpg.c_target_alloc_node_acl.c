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
typedef  int u32 ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {int /*<<< orphan*/  acl_index; struct se_portal_group* se_tpg; int /*<<< orphan*/  initiatorname; int /*<<< orphan*/  acl_pr_ref_count; int /*<<< orphan*/  lun_entry_mutex; int /*<<< orphan*/  nacl_sess_lock; int /*<<< orphan*/  acl_free_comp; int /*<<< orphan*/  acl_kref; int /*<<< orphan*/  lun_entry_hlist; int /*<<< orphan*/  acl_sess_list; int /*<<< orphan*/  acl_list; } ;
struct TYPE_2__ {int (* tpg_get_default_depth ) (struct se_portal_group*) ;int /*<<< orphan*/  (* set_default_node_attributes ) (struct se_node_acl*) ;int /*<<< orphan*/  node_acl_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCSI_AUTH_INTR_INDEX ; 
 int /*<<< orphan*/  TRANSPORT_IQN_LEN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct se_node_acl* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_get_new_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned char const*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int stub1 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub2 (struct se_node_acl*) ; 
 int /*<<< orphan*/  target_set_nacl_queue_depth (struct se_portal_group*,struct se_node_acl*,int) ; 

__attribute__((used)) static struct se_node_acl *target_alloc_node_acl(struct se_portal_group *tpg,
		const unsigned char *initiatorname)
{
	struct se_node_acl *acl;
	u32 queue_depth;

	acl = kzalloc(max(sizeof(*acl), tpg->se_tpg_tfo->node_acl_size),
			GFP_KERNEL);
	if (!acl)
		return NULL;

	INIT_LIST_HEAD(&acl->acl_list);
	INIT_LIST_HEAD(&acl->acl_sess_list);
	INIT_HLIST_HEAD(&acl->lun_entry_hlist);
	kref_init(&acl->acl_kref);
	init_completion(&acl->acl_free_comp);
	spin_lock_init(&acl->nacl_sess_lock);
	mutex_init(&acl->lun_entry_mutex);
	atomic_set(&acl->acl_pr_ref_count, 0);

	if (tpg->se_tpg_tfo->tpg_get_default_depth)
		queue_depth = tpg->se_tpg_tfo->tpg_get_default_depth(tpg);
	else
		queue_depth = 1;
	target_set_nacl_queue_depth(tpg, acl, queue_depth);

	snprintf(acl->initiatorname, TRANSPORT_IQN_LEN, "%s", initiatorname);
	acl->se_tpg = tpg;
	acl->acl_index = scsi_get_new_index(SCSI_AUTH_INTR_INDEX);

	tpg->se_tpg_tfo->set_default_node_attributes(acl);

	return acl;
}