#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  wait; } ;
struct z_erofs_vle_unzip_io {int /*<<< orphan*/  pending_bios; TYPE_2__ u; } ;
struct z_erofs_vle_frontend {int /*<<< orphan*/  owned_head; TYPE_1__* inode; } ;
struct super_block {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_3__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int __FSIO_1 ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  z_erofs_vle_submit_all (struct super_block*,int /*<<< orphan*/ ,struct list_head*,struct z_erofs_vle_unzip_io*,int) ; 
 int /*<<< orphan*/  z_erofs_vle_unzip_all (struct super_block*,struct z_erofs_vle_unzip_io*,struct list_head*) ; 

__attribute__((used)) static void z_erofs_submit_and_unzip(struct z_erofs_vle_frontend *f,
				     struct list_head *pagepool,
				     bool force_fg)
{
	struct super_block *sb = f->inode->i_sb;
	struct z_erofs_vle_unzip_io io[1 + __FSIO_1];

	if (!z_erofs_vle_submit_all(sb, f->owned_head, pagepool, io, force_fg))
		return;

#ifdef EROFS_FS_HAS_MANAGED_CACHE
	z_erofs_vle_unzip_all(sb, &io[0], pagepool);
#endif
	if (!force_fg)
		return;

	/* wait until all bios are completed */
	wait_event(io[__FSIO_1].u.wait,
		!atomic_read(&io[__FSIO_1].pending_bios));

	/* let's synchronous decompression */
	z_erofs_vle_unzip_all(sb, &io[__FSIO_1], pagepool);
}