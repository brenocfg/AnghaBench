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
struct dev_info {int id; } ;
struct cfmuxl {int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/ * dn_cache; int /*<<< orphan*/  frml_list; } ;
struct cflayer {scalar_t__ id; } ;

/* Variables and functions */
 int DN_CACHE_SIZE ; 
 struct cflayer* get_from_id (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct cflayer*) ; 
 struct cflayer* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cflayer *get_dn(struct cfmuxl *muxl, struct dev_info *dev_info)
{
	struct cflayer *dn;
	int idx = dev_info->id % DN_CACHE_SIZE;
	dn = rcu_dereference(muxl->dn_cache[idx]);
	if (dn == NULL || dn->id != dev_info->id) {
		spin_lock_bh(&muxl->transmit_lock);
		dn = get_from_id(&muxl->frml_list, dev_info->id);
		rcu_assign_pointer(muxl->dn_cache[idx], dn);
		spin_unlock_bh(&muxl->transmit_lock);
	}
	return dn;
}