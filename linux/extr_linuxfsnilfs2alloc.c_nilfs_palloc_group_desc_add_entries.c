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
struct nilfs_palloc_group_desc {int /*<<< orphan*/  pg_nfrees; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32
nilfs_palloc_group_desc_add_entries(struct nilfs_palloc_group_desc *desc,
				    spinlock_t *lock, u32 n)
{
	u32 nfree;

	spin_lock(lock);
	le32_add_cpu(&desc->pg_nfrees, n);
	nfree = le32_to_cpu(desc->pg_nfrees);
	spin_unlock(lock);
	return nfree;
}