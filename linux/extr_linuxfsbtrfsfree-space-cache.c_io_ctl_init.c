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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_io_ctl {int num_pages; int check_crcs; struct inode* inode; int /*<<< orphan*/  fs_info; int /*<<< orphan*/  pages; } ;

/* Variables and functions */
 scalar_t__ BTRFS_FREE_INO_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_I (struct inode*) ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_SIZE ; 
 scalar_t__ btrfs_ino (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_sb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct btrfs_io_ctl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int io_ctl_init(struct btrfs_io_ctl *io_ctl, struct inode *inode,
		       int write)
{
	int num_pages;
	int check_crcs = 0;

	num_pages = DIV_ROUND_UP(i_size_read(inode), PAGE_SIZE);

	if (btrfs_ino(BTRFS_I(inode)) != BTRFS_FREE_INO_OBJECTID)
		check_crcs = 1;

	/* Make sure we can fit our crcs and generation into the first page */
	if (write && check_crcs &&
	    (num_pages * sizeof(u32) + sizeof(u64)) > PAGE_SIZE)
		return -ENOSPC;

	memset(io_ctl, 0, sizeof(struct btrfs_io_ctl));

	io_ctl->pages = kcalloc(num_pages, sizeof(struct page *), GFP_NOFS);
	if (!io_ctl->pages)
		return -ENOMEM;

	io_ctl->num_pages = num_pages;
	io_ctl->fs_info = btrfs_sb(inode->i_sb);
	io_ctl->check_crcs = check_crcs;
	io_ctl->inode = inode;

	return 0;
}