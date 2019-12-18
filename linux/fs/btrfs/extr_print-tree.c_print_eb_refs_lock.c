#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct extent_buffer {int /*<<< orphan*/  lock_owner; int /*<<< orphan*/  spinning_readers; int /*<<< orphan*/  spinning_writers; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  blocking_writers; int /*<<< orphan*/  read_locks; int /*<<< orphan*/  write_locks; int /*<<< orphan*/  refs; int /*<<< orphan*/  fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btrfs_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 

__attribute__((used)) static void print_eb_refs_lock(struct extent_buffer *eb)
{
#ifdef CONFIG_BTRFS_DEBUG
	btrfs_info(eb->fs_info,
"refs %u lock (w:%d r:%d bw:%d br:%d sw:%d sr:%d) lock_owner %u current %u",
		   atomic_read(&eb->refs), eb->write_locks,
		   atomic_read(&eb->read_locks),
		   eb->blocking_writers,
		   atomic_read(&eb->blocking_readers),
		   eb->spinning_writers,
		   atomic_read(&eb->spinning_readers),
		   eb->lock_owner, current->pid);
#endif
}