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
typedef  int /*<<< orphan*/  u16 ;
struct net_bridge_port {int dummy; } ;
struct net_bridge {int /*<<< orphan*/  hash_lock; TYPE_1__* dev; } ;
struct ndmsg {int ndm_flags; int /*<<< orphan*/  ndm_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int NTF_EXT_LEARNED ; 
 int NTF_USE ; 
 int br_fdb_external_learn_add (struct net_bridge*,struct net_bridge_port*,unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  br_fdb_update (struct net_bridge*,struct net_bridge_port*,unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int fdb_add_entry (struct net_bridge*,struct net_bridge_port*,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __br_fdb_add(struct ndmsg *ndm, struct net_bridge *br,
			struct net_bridge_port *p, const unsigned char *addr,
			u16 nlh_flags, u16 vid)
{
	int err = 0;

	if (ndm->ndm_flags & NTF_USE) {
		if (!p) {
			pr_info("bridge: RTM_NEWNEIGH %s with NTF_USE is not supported\n",
				br->dev->name);
			return -EINVAL;
		}
		local_bh_disable();
		rcu_read_lock();
		br_fdb_update(br, p, addr, vid, true);
		rcu_read_unlock();
		local_bh_enable();
	} else if (ndm->ndm_flags & NTF_EXT_LEARNED) {
		err = br_fdb_external_learn_add(br, p, addr, vid, true);
	} else {
		spin_lock_bh(&br->hash_lock);
		err = fdb_add_entry(br, p, addr, ndm->ndm_state,
				    nlh_flags, vid, ndm->ndm_flags);
		spin_unlock_bh(&br->hash_lock);
	}

	return err;
}