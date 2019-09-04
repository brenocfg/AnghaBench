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
struct super_block {int /*<<< orphan*/  s_dev; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_anon_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_shutdown_super (struct super_block*) ; 

void kill_anon_super(struct super_block *sb)
{
	dev_t dev = sb->s_dev;
	generic_shutdown_super(sb);
	free_anon_bdev(dev);
}