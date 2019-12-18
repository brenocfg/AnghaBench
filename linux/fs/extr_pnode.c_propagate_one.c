#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mnt_root; } ;
struct mount {int /*<<< orphan*/  mnt_ns; int /*<<< orphan*/  mnt_hash; struct mount* mnt_master; TYPE_1__ mnt; struct mount* mnt_parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  m_dentry; } ;

/* Variables and functions */
 int CL_MAKE_SHARED ; 
 int CL_SLAVE ; 
 scalar_t__ IS_ERR (struct mount*) ; 
 scalar_t__ IS_MNT_MARKED (struct mount*) ; 
 scalar_t__ IS_MNT_NEW (struct mount*) ; 
 scalar_t__ IS_MNT_SHARED (struct mount*) ; 
 int PTR_ERR (struct mount*) ; 
 int /*<<< orphan*/  SET_MNT_MARK (struct mount*) ; 
 struct mount* copy_tree (struct mount*,int /*<<< orphan*/ ,int) ; 
 int count_mounts (int /*<<< orphan*/ ,struct mount*) ; 
 struct mount* dest_master ; 
 struct mount* first_source ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_subdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mount* last_dest ; 
 struct mount* last_source ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  mnt_set_mountpoint (struct mount*,TYPE_2__*,struct mount*) ; 
 int /*<<< orphan*/  mount_lock ; 
 TYPE_2__* mp ; 
 scalar_t__ peers (struct mount*,struct mount*) ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int propagate_one(struct mount *m)
{
	struct mount *child;
	int type;
	/* skip ones added by this propagate_mnt() */
	if (IS_MNT_NEW(m))
		return 0;
	/* skip if mountpoint isn't covered by it */
	if (!is_subdir(mp->m_dentry, m->mnt.mnt_root))
		return 0;
	if (peers(m, last_dest)) {
		type = CL_MAKE_SHARED;
	} else {
		struct mount *n, *p;
		bool done;
		for (n = m; ; n = p) {
			p = n->mnt_master;
			if (p == dest_master || IS_MNT_MARKED(p))
				break;
		}
		do {
			struct mount *parent = last_source->mnt_parent;
			if (last_source == first_source)
				break;
			done = parent->mnt_master == p;
			if (done && peers(n, parent))
				break;
			last_source = last_source->mnt_master;
		} while (!done);

		type = CL_SLAVE;
		/* beginning of peer group among the slaves? */
		if (IS_MNT_SHARED(m))
			type |= CL_MAKE_SHARED;
	}
		
	child = copy_tree(last_source, last_source->mnt.mnt_root, type);
	if (IS_ERR(child))
		return PTR_ERR(child);
	mnt_set_mountpoint(m, mp, child);
	last_dest = m;
	last_source = child;
	if (m->mnt_master != dest_master) {
		read_seqlock_excl(&mount_lock);
		SET_MNT_MARK(m->mnt_master);
		read_sequnlock_excl(&mount_lock);
	}
	hlist_add_head(&child->mnt_hash, list);
	return count_mounts(m->mnt_ns, child);
}