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
struct buffer_head {int /*<<< orphan*/  b_rb_node; } ;
struct block_device {int /*<<< orphan*/  bd_bh_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void buffer_head_remove(struct block_device *bdev, struct buffer_head *bh)
{
    rb_erase(&bh->b_rb_node, &bdev->bd_bh_root);
}