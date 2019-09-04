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
struct the_nilfs {int /*<<< orphan*/ * ns_sbh; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct the_nilfs*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ nilfs_init (struct the_nilfs*) ; 
 int /*<<< orphan*/  nilfs_sysfs_delete_device_group (struct the_nilfs*) ; 

void destroy_nilfs(struct the_nilfs *nilfs)
{
	might_sleep();
	if (nilfs_init(nilfs)) {
		nilfs_sysfs_delete_device_group(nilfs);
		brelse(nilfs->ns_sbh[0]);
		brelse(nilfs->ns_sbh[1]);
	}
	kfree(nilfs);
}