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
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {unsigned long len; int lock_nested; scalar_t__ write_locks; int /*<<< orphan*/  read_locks; int /*<<< orphan*/  spinning_readers; scalar_t__ spinning_writers; int /*<<< orphan*/  io_pages; int /*<<< orphan*/  refs; int /*<<< orphan*/  refs_lock; int /*<<< orphan*/  leak_list; int /*<<< orphan*/  read_lock_wq; int /*<<< orphan*/  write_lock_wq; scalar_t__ blocking_writers; int /*<<< orphan*/  blocking_readers; int /*<<< orphan*/  lock; scalar_t__ bflags; struct btrfs_fs_info* fs_info; int /*<<< orphan*/  start; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 unsigned long BTRFS_MAX_METADATA_BLOCKSIZE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int GFP_NOFS ; 
 unsigned long MAX_INLINE_EXTENT_BUFFER_SIZE ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  btrfs_leak_debug_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffers ; 
 int /*<<< orphan*/  extent_buffer_cache ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct extent_buffer* kmem_cache_zalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct extent_buffer *
__alloc_extent_buffer(struct btrfs_fs_info *fs_info, u64 start,
		      unsigned long len)
{
	struct extent_buffer *eb = NULL;

	eb = kmem_cache_zalloc(extent_buffer_cache, GFP_NOFS|__GFP_NOFAIL);
	eb->start = start;
	eb->len = len;
	eb->fs_info = fs_info;
	eb->bflags = 0;
	rwlock_init(&eb->lock);
	atomic_set(&eb->blocking_readers, 0);
	eb->blocking_writers = 0;
	eb->lock_nested = false;
	init_waitqueue_head(&eb->write_lock_wq);
	init_waitqueue_head(&eb->read_lock_wq);

	btrfs_leak_debug_add(&eb->leak_list, &buffers);

	spin_lock_init(&eb->refs_lock);
	atomic_set(&eb->refs, 1);
	atomic_set(&eb->io_pages, 0);

	/*
	 * Sanity checks, currently the maximum is 64k covered by 16x 4k pages
	 */
	BUILD_BUG_ON(BTRFS_MAX_METADATA_BLOCKSIZE
		> MAX_INLINE_EXTENT_BUFFER_SIZE);
	BUG_ON(len > MAX_INLINE_EXTENT_BUFFER_SIZE);

#ifdef CONFIG_BTRFS_DEBUG
	eb->spinning_writers = 0;
	atomic_set(&eb->spinning_readers, 0);
	atomic_set(&eb->read_locks, 0);
	eb->write_locks = 0;
#endif

	return eb;
}