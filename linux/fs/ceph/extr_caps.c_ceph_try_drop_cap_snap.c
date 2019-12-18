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
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_flags; int /*<<< orphan*/  i_cap_snaps; } ;
struct TYPE_2__ {scalar_t__ tid; } ;
struct ceph_cap_snap {int /*<<< orphan*/  ci_item; int /*<<< orphan*/  context; TYPE_1__ cap_flush; int /*<<< orphan*/  follows; int /*<<< orphan*/  dirty_pages; int /*<<< orphan*/  writing; int /*<<< orphan*/  need_flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  CEPH_I_FLUSH_SNAPS ; 
 int /*<<< orphan*/  ceph_put_cap_snap (struct ceph_cap_snap*) ; 
 int /*<<< orphan*/  ceph_put_snap_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_cap_snap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_try_drop_cap_snap(struct ceph_inode_info *ci,
				  struct ceph_cap_snap *capsnap)
{
	if (!capsnap->need_flush &&
	    !capsnap->writing && !capsnap->dirty_pages) {
		dout("dropping cap_snap %p follows %llu\n",
		     capsnap, capsnap->follows);
		BUG_ON(capsnap->cap_flush.tid > 0);
		ceph_put_snap_context(capsnap->context);
		if (!list_is_last(&capsnap->ci_item, &ci->i_cap_snaps))
			ci->i_ceph_flags |= CEPH_I_FLUSH_SNAPS;

		list_del(&capsnap->ci_item);
		ceph_put_cap_snap(capsnap);
		return 1;
	}
	return 0;
}