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
struct buffer_head {int /*<<< orphan*/  b_assoc_buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_replace_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nilfs_list_replace_buffer(struct buffer_head *old_bh,
				      struct buffer_head *new_bh)
{
	BUG_ON(!list_empty(&new_bh->b_assoc_buffers));

	list_replace_init(&old_bh->b_assoc_buffers, &new_bh->b_assoc_buffers);
	/* The caller must release old_bh */
}