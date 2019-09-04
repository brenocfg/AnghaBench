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
struct nilfs_palloc_group_desc {int /*<<< orphan*/  pg_nfrees; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long
nilfs_palloc_group_desc_nfrees(const struct nilfs_palloc_group_desc *desc,
			       spinlock_t *lock)
{
	unsigned long nfree;

	spin_lock(lock);
	nfree = le32_to_cpu(desc->pg_nfrees);
	spin_unlock(lock);
	return nfree;
}