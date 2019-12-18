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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {scalar_t__* slots; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int btrfs_search_slot (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_path*,int,int) ; 

__attribute__((used)) static int btrfs_search_prev_slot(struct btrfs_trans_handle *trans,
				  struct btrfs_root *root,
				  struct btrfs_key *key, struct btrfs_path *p,
				  int ins_len, int cow)
{
	int ret;

	ret = btrfs_search_slot(trans, root, key, p, ins_len, cow);
	if (ret < 0)
		return ret;

	if (ret == 0) {
		ASSERT(0);
		return -EIO;
	}

	if (p->slots[0] == 0) {
		ASSERT(0);
		return -EIO;
	}
	p->slots[0]--;

	return 0;
}