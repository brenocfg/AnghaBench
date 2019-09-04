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
struct file_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  filelock_cache ; 
 struct file_lock* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  locks_init_lock_heads (struct file_lock*) ; 

struct file_lock *locks_alloc_lock(void)
{
	struct file_lock *fl = kmem_cache_zalloc(filelock_cache, GFP_KERNEL);

	if (fl)
		locks_init_lock_heads(fl);

	return fl;
}