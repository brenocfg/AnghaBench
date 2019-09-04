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
typedef  scalar_t__ z_erofs_vle_owned_workgrp_t ;
struct z_erofs_vle_workgroup {int /*<<< orphan*/  next; } ;
struct z_erofs_vle_unzip_io {scalar_t__ head; } ;
struct super_block {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_BUGON (int) ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_EROFS_VLE_WORKGRP_NIL ; 
 scalar_t__ Z_EROFS_VLE_WORKGRP_TAIL ; 
 scalar_t__ Z_EROFS_VLE_WORKGRP_TAIL_CLOSED ; 
 int /*<<< orphan*/  z_erofs_vle_unzip (struct super_block*,struct z_erofs_vle_workgroup*,struct list_head*) ; 

__attribute__((used)) static void z_erofs_vle_unzip_all(struct super_block *sb,
				  struct z_erofs_vle_unzip_io *io,
				  struct list_head *page_pool)
{
	z_erofs_vle_owned_workgrp_t owned = io->head;

	while (owned != Z_EROFS_VLE_WORKGRP_TAIL_CLOSED) {
		struct z_erofs_vle_workgroup *grp;

		/* no possible that 'owned' equals Z_EROFS_WORK_TPTR_TAIL */
		DBG_BUGON(owned == Z_EROFS_VLE_WORKGRP_TAIL);

		/* no possible that 'owned' equals NULL */
		DBG_BUGON(owned == Z_EROFS_VLE_WORKGRP_NIL);

		grp = owned;
		owned = READ_ONCE(grp->next);

		z_erofs_vle_unzip(sb, grp, page_pool);
	}
}