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

/* Variables and functions */
 int __btrfs_end_transaction (struct btrfs_trans_handle*,int) ; 

int btrfs_end_transaction_throttle(struct btrfs_trans_handle *trans)
{
	return __btrfs_end_transaction(trans, 1);
}