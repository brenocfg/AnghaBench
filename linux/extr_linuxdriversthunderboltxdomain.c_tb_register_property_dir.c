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
 int EAGAIN ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  TB_PROPERTY_TYPE_DIRECTORY ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rebuild_property_block () ; 
 int /*<<< orphan*/  remove_directory (char const*,struct tb_property_dir*) ; 
 int strlen (char const*) ; 
 int tb_property_add_dir (int /*<<< orphan*/ ,char const*,struct tb_property_dir*) ; 
 scalar_t__ tb_property_find (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_all_xdomains () ; 
 int /*<<< orphan*/  xdomain_lock ; 
 int /*<<< orphan*/  xdomain_property_dir ; 

int tb_register_property_dir(const char *key, struct tb_property_dir *dir)
{
	int ret;

	if (WARN_ON(!xdomain_property_dir))
		return -EAGAIN;

	if (!key || strlen(key) > 8)
		return -EINVAL;

	mutex_lock(&xdomain_lock);
	if (tb_property_find(xdomain_property_dir, key,
			     TB_PROPERTY_TYPE_DIRECTORY)) {
		ret = -EEXIST;
		goto err_unlock;
	}

	ret = tb_property_add_dir(xdomain_property_dir, key, dir);
	if (ret)
		goto err_unlock;

	ret = rebuild_property_block();
	if (ret) {
		remove_directory(key, dir);
		goto err_unlock;
	}

	mutex_unlock(&xdomain_lock);
	update_all_xdomains();
	return 0;

err_unlock:
	mutex_unlock(&xdomain_lock);
	return ret;
}