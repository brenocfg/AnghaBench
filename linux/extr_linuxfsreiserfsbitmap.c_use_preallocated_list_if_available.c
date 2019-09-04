#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_4__ {struct inode* inode; } ;
typedef  TYPE_1__ reiserfs_blocknr_hint_t ;
typedef  int /*<<< orphan*/  b_blocknr_t ;
struct TYPE_5__ {scalar_t__ i_prealloc_count; int /*<<< orphan*/  i_prealloc_list; int /*<<< orphan*/  i_prealloc_block; } ;

/* Variables and functions */
 TYPE_3__* REISERFS_I (struct inode*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int use_preallocated_list_if_available(reiserfs_blocknr_hint_t * hint,
					      b_blocknr_t * new_blocknrs,
					      int amount_needed)
{
	struct inode *inode = hint->inode;

	if (REISERFS_I(inode)->i_prealloc_count > 0) {
		while (amount_needed) {

			*new_blocknrs++ = REISERFS_I(inode)->i_prealloc_block++;
			REISERFS_I(inode)->i_prealloc_count--;

			amount_needed--;

			if (REISERFS_I(inode)->i_prealloc_count <= 0) {
				list_del(&REISERFS_I(inode)->i_prealloc_list);
				break;
			}
		}
	}
	/* return amount still needed after using preallocated blocks */
	return amount_needed;
}