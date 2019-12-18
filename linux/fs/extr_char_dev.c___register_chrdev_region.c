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
struct char_device_struct {unsigned int major; unsigned int baseminor; unsigned int minorct; struct char_device_struct* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int CHRDEV_MAJOR_MAX ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct char_device_struct* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MINORMASK ; 
 struct char_device_struct** chrdevs ; 
 int /*<<< orphan*/  chrdevs_lock ; 
 int find_dynamic_major () ; 
 int /*<<< orphan*/  kfree (struct char_device_struct*) ; 
 struct char_device_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 int major_to_index (unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,...) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct char_device_struct *
__register_chrdev_region(unsigned int major, unsigned int baseminor,
			   int minorct, const char *name)
{
	struct char_device_struct *cd, *curr, *prev = NULL;
	int ret;
	int i;

	if (major >= CHRDEV_MAJOR_MAX) {
		pr_err("CHRDEV \"%s\" major requested (%u) is greater than the maximum (%u)\n",
		       name, major, CHRDEV_MAJOR_MAX-1);
		return ERR_PTR(-EINVAL);
	}

	if (minorct > MINORMASK + 1 - baseminor) {
		pr_err("CHRDEV \"%s\" minor range requested (%u-%u) is out of range of maximum range (%u-%u) for a single major\n",
			name, baseminor, baseminor + minorct - 1, 0, MINORMASK);
		return ERR_PTR(-EINVAL);
	}

	cd = kzalloc(sizeof(struct char_device_struct), GFP_KERNEL);
	if (cd == NULL)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&chrdevs_lock);

	if (major == 0) {
		ret = find_dynamic_major();
		if (ret < 0) {
			pr_err("CHRDEV \"%s\" dynamic allocation region is full\n",
			       name);
			goto out;
		}
		major = ret;
	}

	ret = -EBUSY;
	i = major_to_index(major);
	for (curr = chrdevs[i]; curr; prev = curr, curr = curr->next) {
		if (curr->major < major)
			continue;

		if (curr->major > major)
			break;

		if (curr->baseminor + curr->minorct <= baseminor)
			continue;

		if (curr->baseminor >= baseminor + minorct)
			break;

		goto out;
	}

	cd->major = major;
	cd->baseminor = baseminor;
	cd->minorct = minorct;
	strlcpy(cd->name, name, sizeof(cd->name));

	if (!prev) {
		cd->next = curr;
		chrdevs[i] = cd;
	} else {
		cd->next = prev->next;
		prev->next = cd;
	}

	mutex_unlock(&chrdevs_lock);
	return cd;
out:
	mutex_unlock(&chrdevs_lock);
	kfree(cd);
	return ERR_PTR(ret);
}