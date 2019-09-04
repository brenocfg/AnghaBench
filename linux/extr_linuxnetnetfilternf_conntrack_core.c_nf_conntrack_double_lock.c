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
struct net {int dummy; } ;

/* Variables and functions */
 unsigned int CONNTRACK_LOCKS ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  nf_conntrack_double_unlock (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  nf_conntrack_generation ; 
 int /*<<< orphan*/  nf_conntrack_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nf_conntrack_locks ; 
 scalar_t__ read_seqcount_retry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nf_conntrack_double_lock(struct net *net, unsigned int h1,
				     unsigned int h2, unsigned int sequence)
{
	h1 %= CONNTRACK_LOCKS;
	h2 %= CONNTRACK_LOCKS;
	if (h1 <= h2) {
		nf_conntrack_lock(&nf_conntrack_locks[h1]);
		if (h1 != h2)
			spin_lock_nested(&nf_conntrack_locks[h2],
					 SINGLE_DEPTH_NESTING);
	} else {
		nf_conntrack_lock(&nf_conntrack_locks[h2]);
		spin_lock_nested(&nf_conntrack_locks[h1],
				 SINGLE_DEPTH_NESTING);
	}
	if (read_seqcount_retry(&nf_conntrack_generation, sequence)) {
		nf_conntrack_double_unlock(h1, h2);
		return true;
	}
	return false;
}