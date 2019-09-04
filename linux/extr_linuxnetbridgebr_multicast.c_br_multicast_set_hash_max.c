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
typedef  unsigned long u32 ;
struct net_bridge_mdb_htable {unsigned long size; scalar_t__ old; } ;
struct net_bridge {unsigned long hash_max; int /*<<< orphan*/  multicast_lock; int /*<<< orphan*/  hash_elasticity; int /*<<< orphan*/  mdb; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int br_mdb_rehash (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (unsigned long) ; 
 struct net_bridge_mdb_htable* mlock_dereference (int /*<<< orphan*/ ,struct net_bridge*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int br_multicast_set_hash_max(struct net_bridge *br, unsigned long val)
{
	int err = -EINVAL;
	u32 old;
	struct net_bridge_mdb_htable *mdb;

	spin_lock_bh(&br->multicast_lock);
	if (!is_power_of_2(val))
		goto unlock;

	mdb = mlock_dereference(br->mdb, br);
	if (mdb && val < mdb->size)
		goto unlock;

	err = 0;

	old = br->hash_max;
	br->hash_max = val;

	if (mdb) {
		if (mdb->old) {
			err = -EEXIST;
rollback:
			br->hash_max = old;
			goto unlock;
		}

		err = br_mdb_rehash(&br->mdb, br->hash_max,
				    br->hash_elasticity);
		if (err)
			goto rollback;
	}

unlock:
	spin_unlock_bh(&br->multicast_lock);

	return err;
}