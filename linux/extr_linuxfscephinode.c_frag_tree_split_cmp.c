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
struct ceph_frag_tree_split {int /*<<< orphan*/  frag; } ;

/* Variables and functions */
 int ceph_frag_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int frag_tree_split_cmp(const void *l, const void *r)
{
	struct ceph_frag_tree_split *ls = (struct ceph_frag_tree_split*)l;
	struct ceph_frag_tree_split *rs = (struct ceph_frag_tree_split*)r;
	return ceph_frag_compare(le32_to_cpu(ls->frag),
				 le32_to_cpu(rs->frag));
}