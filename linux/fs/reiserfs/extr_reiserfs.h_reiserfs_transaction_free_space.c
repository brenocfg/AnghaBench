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
struct reiserfs_transaction_handle {int t_blocks_allocated; int t_blocks_logged; } ;

/* Variables and functions */

__attribute__((used)) static inline int reiserfs_transaction_free_space(struct reiserfs_transaction_handle *th)
{
	return th->t_blocks_allocated - th->t_blocks_logged;
}