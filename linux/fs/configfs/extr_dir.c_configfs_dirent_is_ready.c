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
struct configfs_dirent {int s_type; } ;

/* Variables and functions */
 int CONFIGFS_USET_CREATING ; 
 int /*<<< orphan*/  configfs_dirent_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int configfs_dirent_is_ready(struct configfs_dirent *sd)
{
	int ret;

	spin_lock(&configfs_dirent_lock);
	ret = !(sd->s_type & CONFIGFS_USET_CREATING);
	spin_unlock(&configfs_dirent_lock);

	return ret;
}