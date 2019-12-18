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
typedef  scalar_t__ u64 ;
struct inode {struct address_space* i_mapping; } ;
struct address_space {scalar_t__ nrpages; } ;
typedef  scalar_t__ pgoff_t ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ULONG_MAX ; 
 scalar_t__ i_size_read (struct inode*) ; 
 scalar_t__ page_cache_next_miss (struct address_space*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static u64 pnfs_num_cont_bytes(struct inode *inode, pgoff_t idx)
{
	struct address_space *mapping = inode->i_mapping;
	pgoff_t end;

	/* Optimize common case that writes from 0 to end of file */
	end = DIV_ROUND_UP(i_size_read(inode), PAGE_SIZE);
	if (end != inode->i_mapping->nrpages) {
		rcu_read_lock();
		end = page_cache_next_miss(mapping, idx + 1, ULONG_MAX);
		rcu_read_unlock();
	}

	if (!end)
		return i_size_read(inode) - (idx << PAGE_SHIFT);
	else
		return (end - idx) << PAGE_SHIFT;
}