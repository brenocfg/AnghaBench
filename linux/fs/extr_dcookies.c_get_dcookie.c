#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct path {TYPE_1__* dentry; } ;
struct dcookie_struct {int dummy; } ;
struct TYPE_2__ {int d_flags; } ;

/* Variables and functions */
 int DCACHE_COOKIE ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct dcookie_struct* alloc_dcookie (struct path const*) ; 
 int /*<<< orphan*/  dcookie_mutex ; 
 unsigned long dcookie_value (struct dcookie_struct*) ; 
 struct dcookie_struct* find_dcookie (unsigned long) ; 
 int /*<<< orphan*/  is_live () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int get_dcookie(const struct path *path, unsigned long *cookie)
{
	int err = 0;
	struct dcookie_struct * dcs;

	mutex_lock(&dcookie_mutex);

	if (!is_live()) {
		err = -EINVAL;
		goto out;
	}

	if (path->dentry->d_flags & DCACHE_COOKIE) {
		dcs = find_dcookie((unsigned long)path->dentry);
	} else {
		dcs = alloc_dcookie(path);
		if (!dcs) {
			err = -ENOMEM;
			goto out;
		}
	}

	*cookie = dcookie_value(dcs);

out:
	mutex_unlock(&dcookie_mutex);
	return err;
}