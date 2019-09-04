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
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  wait; } ;
struct z_erofs_vle_unzip_io {int /*<<< orphan*/  head; TYPE_1__ u; int /*<<< orphan*/  pending_bios; } ;
struct z_erofs_vle_unzip_io_sb {struct super_block* sb; struct z_erofs_vle_unzip_io io; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_EROFS_VLE_WORKGRP_TAIL_CLOSED ; 
 int __GFP_NOFAIL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct z_erofs_vle_unzip_io_sb* kvzalloc (int,int) ; 
 int /*<<< orphan*/  z_erofs_vle_unzip_wq ; 

__attribute__((used)) static inline struct z_erofs_vle_unzip_io *
prepare_io_handler(struct super_block *sb,
		   struct z_erofs_vle_unzip_io *io,
		   bool background)
{
	struct z_erofs_vle_unzip_io_sb *iosb;

	if (!background) {
		/* waitqueue available for foreground io */
		BUG_ON(io == NULL);

		init_waitqueue_head(&io->u.wait);
		atomic_set(&io->pending_bios, 0);
		goto out;
	}

	if (io != NULL)
		BUG();
	else {
		/* allocate extra io descriptor for background io */
		iosb = kvzalloc(sizeof(struct z_erofs_vle_unzip_io_sb),
			GFP_KERNEL | __GFP_NOFAIL);
		BUG_ON(iosb == NULL);

		io = &iosb->io;
	}

	iosb->sb = sb;
	INIT_WORK(&io->u.work, z_erofs_vle_unzip_wq);
out:
	io->head = Z_EROFS_VLE_WORKGRP_TAIL_CLOSED;
	return io;
}