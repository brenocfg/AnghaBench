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
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int __btrfs_mod_ref (struct btrfs_trans_handle*,struct btrfs_root*,struct extent_buffer*,int,int) ; 

int btrfs_inc_ref(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		  struct extent_buffer *buf, int full_backref)
{
	return __btrfs_mod_ref(trans, root, buf, full_backref, 1);
}