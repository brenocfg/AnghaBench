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
struct TYPE_2__ {int mem_blocks; int mem_block_size; } ;
struct ar9170 {int /*<<< orphan*/  mem_lock; TYPE_1__ fw; int /*<<< orphan*/  mem_free_blocks; int /*<<< orphan*/  mem_allocs; int /*<<< orphan*/  mem_bitmap; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,int /*<<< orphan*/ ,size_t,char*,int,int,...) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int bitmap_weight (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *carl9170_debugfs_mem_usage_read(struct ar9170 *ar, char *buf,
					     size_t bufsize, ssize_t *len)
{
	spin_lock_bh(&ar->mem_lock);

	ADD(buf, *len, bufsize, "jar: [%*pb]\n",
	    ar->fw.mem_blocks, ar->mem_bitmap);

	ADD(buf, *len, bufsize, "cookies: used:%3d / total:%3d, allocs:%d\n",
	    bitmap_weight(ar->mem_bitmap, ar->fw.mem_blocks),
	    ar->fw.mem_blocks, atomic_read(&ar->mem_allocs));

	ADD(buf, *len, bufsize, "memory: free:%3d (%3d KiB) / total:%3d KiB)\n",
	    atomic_read(&ar->mem_free_blocks),
	    (atomic_read(&ar->mem_free_blocks) * ar->fw.mem_block_size) / 1024,
	    (ar->fw.mem_blocks * ar->fw.mem_block_size) / 1024);

	spin_unlock_bh(&ar->mem_lock);

	return buf;
}