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
struct super_block {int dummy; } ;
struct block_device {int dummy; } ;

/* Variables and functions */
 struct super_block* __get_super_thawed (struct block_device*,int) ; 

struct super_block *get_super_exclusive_thawed(struct block_device *bdev)
{
	return __get_super_thawed(bdev, true);
}