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
struct the_nilfs {unsigned int ns_mount_state; int /*<<< orphan*/  ns_sem; } ;

/* Variables and functions */
 unsigned int NILFS_VALID_FS ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int nilfs_valid_fs(struct the_nilfs *nilfs)
{
	unsigned int valid_fs;

	down_read(&nilfs->ns_sem);
	valid_fs = (nilfs->ns_mount_state & NILFS_VALID_FS);
	up_read(&nilfs->ns_sem);
	return valid_fs;
}