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

/* Variables and functions */
 int CONNTRACK_LOCKS ; 
 int /*<<< orphan*/ * nf_conntrack_locks ; 
 int nf_conntrack_locks_all ; 
 int /*<<< orphan*/  nf_conntrack_locks_all_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_conntrack_all_lock(void)
{
	int i;

	spin_lock(&nf_conntrack_locks_all_lock);

	nf_conntrack_locks_all = true;

	for (i = 0; i < CONNTRACK_LOCKS; i++) {
		spin_lock(&nf_conntrack_locks[i]);

		/* This spin_unlock provides the "release" to ensure that
		 * nf_conntrack_locks_all==true is visible to everyone that
		 * acquired spin_lock(&nf_conntrack_locks[]).
		 */
		spin_unlock(&nf_conntrack_locks[i]);
	}
}