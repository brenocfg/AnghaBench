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
struct address_space {int /*<<< orphan*/  i_mmap; int /*<<< orphan*/  private_lock; int /*<<< orphan*/  private_list; int /*<<< orphan*/  i_mmap_rwsem; int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int __GFP_ACCOUNT ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __address_space_init_once(struct address_space *mapping)
{
	INIT_RADIX_TREE(&mapping->i_pages, GFP_ATOMIC | __GFP_ACCOUNT);
	init_rwsem(&mapping->i_mmap_rwsem);
	INIT_LIST_HEAD(&mapping->private_list);
	spin_lock_init(&mapping->private_lock);
	mapping->i_mmap = RB_ROOT_CACHED;
}