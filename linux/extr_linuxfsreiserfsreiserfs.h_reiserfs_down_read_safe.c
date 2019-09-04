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
struct super_block {int dummy; } ;
struct rw_semaphore {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (struct rw_semaphore*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 

__attribute__((used)) static inline void
reiserfs_down_read_safe(struct rw_semaphore *sem, struct super_block *s)
{
       int depth;
       depth = reiserfs_write_unlock_nested(s);
       down_read(sem);
       reiserfs_write_lock_nested(s, depth);
}