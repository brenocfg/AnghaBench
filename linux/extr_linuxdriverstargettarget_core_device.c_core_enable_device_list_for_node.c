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
typedef  int /*<<< orphan*/  u64 ;
struct se_portal_group {int dummy; } ;
struct se_node_acl {int /*<<< orphan*/  lun_entry_mutex; int /*<<< orphan*/  lun_entry_hlist; int /*<<< orphan*/  initiatorname; } ;
struct se_lun_acl {int /*<<< orphan*/  lun_deve_lock; int /*<<< orphan*/  lun_deve_list; } ;
struct se_lun {int /*<<< orphan*/  lun_deve_lock; int /*<<< orphan*/  lun_deve_list; } ;
struct se_dev_entry {int lun_access_ro; int /*<<< orphan*/  lun_link; int /*<<< orphan*/  link; int /*<<< orphan*/ * se_lun_acl; int /*<<< orphan*/ * se_lun; int /*<<< orphan*/  pr_comp; int /*<<< orphan*/  pr_kref; int /*<<< orphan*/  attach_count; int /*<<< orphan*/  creation_time; int /*<<< orphan*/  mapped_lun; int /*<<< orphan*/  ua_list; int /*<<< orphan*/  ua_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct se_dev_entry*) ; 
 int /*<<< orphan*/  kfree_rcu (struct se_dev_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct se_dev_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,struct se_lun_acl*) ; 
 struct se_lun_acl* rcu_dereference_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_luns_data_has_changed (struct se_node_acl*,struct se_dev_entry*,int) ; 
 struct se_dev_entry* target_nacl_find_deve (struct se_node_acl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pr_kref_release ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int core_enable_device_list_for_node(
	struct se_lun *lun,
	struct se_lun_acl *lun_acl,
	u64 mapped_lun,
	bool lun_access_ro,
	struct se_node_acl *nacl,
	struct se_portal_group *tpg)
{
	struct se_dev_entry *orig, *new;

	new = kzalloc(sizeof(*new), GFP_KERNEL);
	if (!new) {
		pr_err("Unable to allocate se_dev_entry memory\n");
		return -ENOMEM;
	}

	spin_lock_init(&new->ua_lock);
	INIT_LIST_HEAD(&new->ua_list);
	INIT_LIST_HEAD(&new->lun_link);

	new->mapped_lun = mapped_lun;
	kref_init(&new->pr_kref);
	init_completion(&new->pr_comp);

	new->lun_access_ro = lun_access_ro;
	new->creation_time = get_jiffies_64();
	new->attach_count++;

	mutex_lock(&nacl->lun_entry_mutex);
	orig = target_nacl_find_deve(nacl, mapped_lun);
	if (orig && orig->se_lun) {
		struct se_lun *orig_lun = rcu_dereference_check(orig->se_lun,
					lockdep_is_held(&nacl->lun_entry_mutex));

		if (orig_lun != lun) {
			pr_err("Existing orig->se_lun doesn't match new lun"
			       " for dynamic -> explicit NodeACL conversion:"
				" %s\n", nacl->initiatorname);
			mutex_unlock(&nacl->lun_entry_mutex);
			kfree(new);
			return -EINVAL;
		}
		if (orig->se_lun_acl != NULL) {
			pr_warn_ratelimited("Detected existing explicit"
				" se_lun_acl->se_lun_group reference for %s"
				" mapped_lun: %llu, failing\n",
				 nacl->initiatorname, mapped_lun);
			mutex_unlock(&nacl->lun_entry_mutex);
			kfree(new);
			return -EINVAL;
		}

		rcu_assign_pointer(new->se_lun, lun);
		rcu_assign_pointer(new->se_lun_acl, lun_acl);
		hlist_del_rcu(&orig->link);
		hlist_add_head_rcu(&new->link, &nacl->lun_entry_hlist);
		mutex_unlock(&nacl->lun_entry_mutex);

		spin_lock(&lun->lun_deve_lock);
		list_del(&orig->lun_link);
		list_add_tail(&new->lun_link, &lun->lun_deve_list);
		spin_unlock(&lun->lun_deve_lock);

		kref_put(&orig->pr_kref, target_pr_kref_release);
		wait_for_completion(&orig->pr_comp);

		target_luns_data_has_changed(nacl, new, true);
		kfree_rcu(orig, rcu_head);
		return 0;
	}

	rcu_assign_pointer(new->se_lun, lun);
	rcu_assign_pointer(new->se_lun_acl, lun_acl);
	hlist_add_head_rcu(&new->link, &nacl->lun_entry_hlist);
	mutex_unlock(&nacl->lun_entry_mutex);

	spin_lock(&lun->lun_deve_lock);
	list_add_tail(&new->lun_link, &lun->lun_deve_list);
	spin_unlock(&lun->lun_deve_lock);

	target_luns_data_has_changed(nacl, new, true);
	return 0;
}