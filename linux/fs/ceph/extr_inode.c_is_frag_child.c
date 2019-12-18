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
typedef  scalar_t__ u32 ;
struct ceph_inode_frag {scalar_t__ frag; scalar_t__ split_by; } ;

/* Variables and functions */
 scalar_t__ ceph_frag_bits (scalar_t__) ; 
 int ceph_frag_contains_value (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_frag_make (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_frag_value (scalar_t__) ; 

__attribute__((used)) static bool is_frag_child(u32 f, struct ceph_inode_frag *frag)
{
	if (!frag)
		return f == ceph_frag_make(0, 0);
	if (ceph_frag_bits(f) != ceph_frag_bits(frag->frag) + frag->split_by)
		return false;
	return ceph_frag_contains_value(frag->frag, ceph_frag_value(f));
}