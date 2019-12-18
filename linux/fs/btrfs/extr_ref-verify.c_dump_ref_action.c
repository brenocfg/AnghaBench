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
struct TYPE_2__ {int /*<<< orphan*/  num_refs; int /*<<< orphan*/  offset; int /*<<< orphan*/  owner; int /*<<< orphan*/  parent; int /*<<< orphan*/  root_objectid; } ;
struct ref_action {TYPE_1__ ref; int /*<<< orphan*/  root; int /*<<< orphan*/  action; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __print_stack_trace (struct btrfs_fs_info*,struct ref_action*) ; 
 int /*<<< orphan*/  btrfs_err (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_ref_action(struct btrfs_fs_info *fs_info,
			    struct ref_action *ra)
{
	btrfs_err(fs_info,
"  Ref action %d, root %llu, ref_root %llu, parent %llu, owner %llu, offset %llu, num_refs %llu",
		  ra->action, ra->root, ra->ref.root_objectid, ra->ref.parent,
		  ra->ref.owner, ra->ref.offset, ra->ref.num_refs);
	__print_stack_trace(fs_info, ra);
}