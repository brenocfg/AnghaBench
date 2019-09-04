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
struct tb_property_dir {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rebuild_property_block () ; 
 scalar_t__ remove_directory (char const*,struct tb_property_dir*) ; 
 int /*<<< orphan*/  update_all_xdomains () ; 
 int /*<<< orphan*/  xdomain_lock ; 

void tb_unregister_property_dir(const char *key, struct tb_property_dir *dir)
{
	int ret = 0;

	mutex_lock(&xdomain_lock);
	if (remove_directory(key, dir))
		ret = rebuild_property_block();
	mutex_unlock(&xdomain_lock);

	if (!ret)
		update_all_xdomains();
}