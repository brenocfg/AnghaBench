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
struct super_block {struct block_device* s_bdev; } ;
struct block_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int test_gfs2_super(struct super_block *s, void *ptr)
{
	struct block_device *bdev = ptr;
	return (bdev == s->s_bdev);
}