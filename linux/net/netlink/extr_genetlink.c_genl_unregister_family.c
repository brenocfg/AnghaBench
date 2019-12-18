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
struct genl_family {int /*<<< orphan*/  attrbuf; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_CMD_DELFAMILY ; 
 int ENOENT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cb_lock ; 
 int /*<<< orphan*/  genl_ctrl_event (int /*<<< orphan*/ ,struct genl_family const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_fam_idr ; 
 int /*<<< orphan*/  genl_family_find_byid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genl_lock_all () ; 
 int /*<<< orphan*/  genl_sk_destructing_cnt ; 
 int /*<<< orphan*/  genl_sk_destructing_waitq ; 
 int /*<<< orphan*/  genl_unlock () ; 
 int /*<<< orphan*/  genl_unlock_all () ; 
 int /*<<< orphan*/  genl_unregister_mc_groups (struct genl_family const*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int genl_unregister_family(const struct genl_family *family)
{
	genl_lock_all();

	if (!genl_family_find_byid(family->id)) {
		genl_unlock_all();
		return -ENOENT;
	}

	genl_unregister_mc_groups(family);

	idr_remove(&genl_fam_idr, family->id);

	up_write(&cb_lock);
	wait_event(genl_sk_destructing_waitq,
		   atomic_read(&genl_sk_destructing_cnt) == 0);
	genl_unlock();

	kfree(family->attrbuf);

	genl_ctrl_event(CTRL_CMD_DELFAMILY, family, NULL, 0);

	return 0;
}