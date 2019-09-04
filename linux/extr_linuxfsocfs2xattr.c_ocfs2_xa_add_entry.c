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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xa_loc {int /*<<< orphan*/  xl_size; TYPE_2__* xl_entry; TYPE_1__* xl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  xe_name_offset; int /*<<< orphan*/  xe_name_hash; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* xlo_add_entry ) (struct ocfs2_xa_loc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ocfs2_xa_loc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_xa_add_entry(struct ocfs2_xa_loc *loc, u32 name_hash)
{
	loc->xl_ops->xlo_add_entry(loc, name_hash);
	loc->xl_entry->xe_name_hash = cpu_to_le32(name_hash);
	/*
	 * We can't leave the new entry's xe_name_offset at zero or
	 * add_namevalue() will go nuts.  We set it to the size of our
	 * storage so that it can never be less than any other entry.
	 */
	loc->xl_entry->xe_name_offset = cpu_to_le16(loc->xl_size);
}