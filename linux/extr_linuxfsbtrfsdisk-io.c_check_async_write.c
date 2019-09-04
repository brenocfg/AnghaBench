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
struct btrfs_inode {int /*<<< orphan*/  sync_writers; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_async_write(struct btrfs_inode *bi)
{
	if (atomic_read(&bi->sync_writers))
		return 0;
#ifdef CONFIG_X86
	if (static_cpu_has(X86_FEATURE_XMM4_2))
		return 0;
#endif
	return 1;
}