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
typedef  int /*<<< orphan*/  u32 ;
struct ceph_inode_info {int dummy; } ;
struct ceph_inode_frag {int split_by; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ceph_inode_frag* __ceph_find_frag (struct ceph_inode_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_frag_contains_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_frag_make (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_frag_make_child (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (struct ceph_inode_frag*,struct ceph_inode_frag*,int) ; 

__attribute__((used)) static u32 __ceph_choose_frag(struct ceph_inode_info *ci, u32 v,
			      struct ceph_inode_frag *pfrag, int *found)
{
	u32 t = ceph_frag_make(0, 0);
	struct ceph_inode_frag *frag;
	unsigned nway, i;
	u32 n;

	if (found)
		*found = 0;

	while (1) {
		WARN_ON(!ceph_frag_contains_value(t, v));
		frag = __ceph_find_frag(ci, t);
		if (!frag)
			break; /* t is a leaf */
		if (frag->split_by == 0) {
			if (pfrag)
				memcpy(pfrag, frag, sizeof(*pfrag));
			if (found)
				*found = 1;
			break;
		}

		/* choose child */
		nway = 1 << frag->split_by;
		dout("choose_frag(%x) %x splits by %d (%d ways)\n", v, t,
		     frag->split_by, nway);
		for (i = 0; i < nway; i++) {
			n = ceph_frag_make_child(t, frag->split_by, i);
			if (ceph_frag_contains_value(n, v)) {
				t = n;
				break;
			}
		}
		BUG_ON(i == nway);
	}
	dout("choose_frag(%x) = %x\n", v, t);

	return t;
}