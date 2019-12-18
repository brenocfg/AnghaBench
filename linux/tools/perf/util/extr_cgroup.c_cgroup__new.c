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
struct cgroup {int fd; int /*<<< orphan*/  name; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct cgroup*) ; 
 int open_cgroup (char const*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 struct cgroup* zalloc (int) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct cgroup *cgroup__new(const char *name)
{
	struct cgroup *cgroup = zalloc(sizeof(*cgroup));

	if (cgroup != NULL) {
		refcount_set(&cgroup->refcnt, 1);

		cgroup->name = strdup(name);
		if (!cgroup->name)
			goto out_err;
		cgroup->fd = open_cgroup(name);
		if (cgroup->fd == -1)
			goto out_free_name;
	}

	return cgroup;

out_free_name:
	zfree(&cgroup->name);
out_err:
	free(cgroup);
	return NULL;
}