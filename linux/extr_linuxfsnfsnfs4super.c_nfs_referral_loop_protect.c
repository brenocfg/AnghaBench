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
struct nfs_referral_count {int referral_count; int /*<<< orphan*/  list; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 int ELOOP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NFS_MAX_NESTED_REFERRALS ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kfree (struct nfs_referral_count*) ; 
 struct nfs_referral_count* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs_referral_count* nfs_find_referral_count () ; 
 int /*<<< orphan*/  nfs_referral_count_list ; 
 int /*<<< orphan*/  nfs_referral_count_list_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_referral_loop_protect(void)
{
	struct nfs_referral_count *p, *new;
	int ret = -ENOMEM;

	new = kmalloc(sizeof(*new), GFP_KERNEL);
	if (!new)
		goto out;
	new->task = current;
	new->referral_count = 1;

	ret = 0;
	spin_lock(&nfs_referral_count_list_lock);
	p = nfs_find_referral_count();
	if (p != NULL) {
		if (p->referral_count >= NFS_MAX_NESTED_REFERRALS)
			ret = -ELOOP;
		else
			p->referral_count++;
	} else {
		list_add(&new->list, &nfs_referral_count_list);
		new = NULL;
	}
	spin_unlock(&nfs_referral_count_list_lock);
	kfree(new);
out:
	return ret;
}