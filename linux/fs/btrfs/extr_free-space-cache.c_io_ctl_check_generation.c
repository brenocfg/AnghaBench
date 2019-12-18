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
typedef  int /*<<< orphan*/  u32 ;
struct btrfs_io_ctl {int num_pages; int size; int /*<<< orphan*/ * cur; int /*<<< orphan*/  fs_info; scalar_t__ check_crcs; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  btrfs_err_rl (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  io_ctl_unmap_page (struct btrfs_io_ctl*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_ctl_check_generation(struct btrfs_io_ctl *io_ctl, u64 generation)
{
	__le64 *gen;

	/*
	 * Skip the crc area.  If we don't check crcs then we just have a 64bit
	 * chunk at the front of the first page.
	 */
	if (io_ctl->check_crcs) {
		io_ctl->cur += sizeof(u32) * io_ctl->num_pages;
		io_ctl->size -= sizeof(u64) +
			(sizeof(u32) * io_ctl->num_pages);
	} else {
		io_ctl->cur += sizeof(u64);
		io_ctl->size -= sizeof(u64) * 2;
	}

	gen = io_ctl->cur;
	if (le64_to_cpu(*gen) != generation) {
		btrfs_err_rl(io_ctl->fs_info,
			"space cache generation (%llu) does not match inode (%llu)",
				*gen, generation);
		io_ctl_unmap_page(io_ctl);
		return -EIO;
	}
	io_ctl->cur += sizeof(u64);
	return 0;
}