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
struct char_device_struct {unsigned int major; unsigned int baseminor; int minorct; struct char_device_struct* next; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int CHRDEV_MAJOR_MAX ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct char_device_struct* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
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
	struct char_device_struct *cd, **cp;
	int ret = 0;
	int i;

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

	if (major >= CHRDEV_MAJOR_MAX) {
		pr_err("CHRDEV \"%s\" major requested (%u) is greater than the maximum (%u)\n",
		       name, major, CHRDEV_MAJOR_MAX-1);
		ret = -EINVAL;
		goto out;
	}

	cd->major = major;
	cd->baseminor = baseminor;
	cd->minorct = minorct;
	strlcpy(cd->name, name, sizeof(cd->name));

	i = major_to_index(major);

	for (cp = &chrdevs[i]; *cp; cp = &(*cp)->next)
		if ((*cp)->major > major ||
		    ((*cp)->major == major &&
		     (((*cp)->baseminor >= baseminor) ||
		      ((*cp)->baseminor + (*cp)->minorct > baseminor))))
			break;

	/* Check for overlapping minor ranges.  */
	if (*cp && (*cp)->major == major) {
		int old_min = (*cp)->baseminor;
		int old_max = (*cp)->baseminor + (*cp)->minorct - 1;
		int new_min = baseminor;
		int new_max = baseminor + minorct - 1;

		/* New driver overlaps from the left.  */
		if (new_max >= old_min && new_max <= old_max) {
			ret = -EBUSY;
			goto out;
		}

		/* New driver overlaps from the right.  */
		if (new_min <= old_max && new_min >= old_min) {
			ret = -EBUSY;
			goto out;
		}
	}

	cd->next = *cp;
	*cp = cd;
	mutex_unlock(&chrdevs_lock);
	return cd;
out:
	mutex_unlock(&chrdevs_lock);
	kfree(cd);
	return ERR_PTR(ret);
}