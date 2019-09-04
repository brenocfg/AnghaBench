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
struct extent_buffer {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void print_eb_refs_lock(struct extent_buffer *eb)
{
#ifdef CONFIG_BTRFS_DEBUG
	btrfs_info(eb->fs_info,
"refs %u lock (w:%d r:%d bw:%d br:%d sw:%d sr:%d) lock_owner %u current %u",
		   atomic_read(&eb->refs), atomic_read(&eb->write_locks),
		   atomic_read(&eb->read_locks),
		   atomic_read(&eb->blocking_writers),
		   atomic_read(&eb->blocking_readers),
		   atomic_read(&eb->spinning_writers),
		   atomic_read(&eb->spinning_readers),
		   eb->lock_owner, current->pid);
#endif
}