#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ceph_cap {scalar_t__ cap_gen; int /*<<< orphan*/  issued; TYPE_1__* ci; TYPE_2__* session; } ;
struct TYPE_4__ {scalar_t__ s_cap_gen; unsigned long s_cap_ttl; int /*<<< orphan*/  s_gen_ttl_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceph_cap_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ *,struct ceph_cap*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int __cap_is_valid(struct ceph_cap *cap)
{
	unsigned long ttl;
	u32 gen;

	spin_lock(&cap->session->s_gen_ttl_lock);
	gen = cap->session->s_cap_gen;
	ttl = cap->session->s_cap_ttl;
	spin_unlock(&cap->session->s_gen_ttl_lock);

	if (cap->cap_gen < gen || time_after_eq(jiffies, ttl)) {
		dout("__cap_is_valid %p cap %p issued %s "
		     "but STALE (gen %u vs %u)\n", &cap->ci->vfs_inode,
		     cap, ceph_cap_string(cap->issued), cap->cap_gen, gen);
		return 0;
	}

	return 1;
}