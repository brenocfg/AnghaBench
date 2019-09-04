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
struct btrfs_block_group_cache {int /*<<< orphan*/  nocow_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_var_event (int /*<<< orphan*/ *,int) ; 

void btrfs_wait_nocow_writers(struct btrfs_block_group_cache *bg)
{
	wait_var_event(&bg->nocow_writers, !atomic_read(&bg->nocow_writers));
}