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
struct configfs_dirent {int /*<<< orphan*/  s_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_configfs_dirent (struct configfs_dirent*) ; 

__attribute__((used)) static inline void configfs_put(struct configfs_dirent * sd)
{
	WARN_ON(!atomic_read(&sd->s_count));
	if (atomic_dec_and_test(&sd->s_count))
		release_configfs_dirent(sd);
}