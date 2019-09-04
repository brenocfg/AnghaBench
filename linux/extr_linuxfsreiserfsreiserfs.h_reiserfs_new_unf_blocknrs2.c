#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct treepath {int dummy; } ;
struct reiserfs_transaction_handle {int dummy; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_3__ {int preallocate; int /*<<< orphan*/  formatted_node; int /*<<< orphan*/  block; struct inode* inode; struct treepath* path; struct reiserfs_transaction_handle* th; } ;
typedef  TYPE_1__ reiserfs_blocknr_hint_t ;
typedef  int /*<<< orphan*/  b_blocknr_t ;

/* Variables and functions */
 int reiserfs_allocate_blocknrs (TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int reiserfs_new_unf_blocknrs2(struct reiserfs_transaction_handle
					     *th, struct inode *inode,
					     b_blocknr_t * new_blocknrs,
					     struct treepath *path,
					     sector_t block)
{
	reiserfs_blocknr_hint_t hint = {
		.th = th,
		.path = path,
		.inode = inode,
		.block = block,
		.formatted_node = 0,
		.preallocate = 1
	};
	return reiserfs_allocate_blocknrs(&hint, new_blocknrs, 1, 0);
}