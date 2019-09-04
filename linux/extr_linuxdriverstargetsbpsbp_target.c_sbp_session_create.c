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
struct sbp_tpg {int /*<<< orphan*/  se_tpg; } ;
struct sbp_target_request {int dummy; } ;
struct sbp_session {int /*<<< orphan*/  se_sess; int /*<<< orphan*/  guid; int /*<<< orphan*/  maint_work; int /*<<< orphan*/  login_list; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  guid_str ;

/* Variables and functions */
 int ENOMEM ; 
 struct sbp_session* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_PROT_NORMAL ; 
 int /*<<< orphan*/  kfree (struct sbp_session*) ; 
 struct sbp_session* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  session_maintenance_work ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_setup_session (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,char*,struct sbp_session*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct sbp_session *sbp_session_create(
		struct sbp_tpg *tpg,
		u64 guid)
{
	struct sbp_session *sess;
	int ret;
	char guid_str[17];

	snprintf(guid_str, sizeof(guid_str), "%016llx", guid);

	sess = kmalloc(sizeof(*sess), GFP_KERNEL);
	if (!sess)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&sess->lock);
	INIT_LIST_HEAD(&sess->login_list);
	INIT_DELAYED_WORK(&sess->maint_work, session_maintenance_work);
	sess->guid = guid;

	sess->se_sess = target_setup_session(&tpg->se_tpg, 128,
					     sizeof(struct sbp_target_request),
					     TARGET_PROT_NORMAL, guid_str,
					     sess, NULL);
	if (IS_ERR(sess->se_sess)) {
		pr_err("failed to init se_session\n");
		ret = PTR_ERR(sess->se_sess);
		kfree(sess);
		return ERR_PTR(ret);
	}

	return sess;
}