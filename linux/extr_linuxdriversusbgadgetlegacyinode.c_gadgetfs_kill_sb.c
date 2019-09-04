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

/* Variables and functions */
 int /*<<< orphan*/ * CHIP ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 
 int /*<<< orphan*/  put_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * the_device ; 

__attribute__((used)) static void
gadgetfs_kill_sb (struct super_block *sb)
{
	kill_litter_super (sb);
	if (the_device) {
		put_dev (the_device);
		the_device = NULL;
	}
	kfree(CHIP);
	CHIP = NULL;
}