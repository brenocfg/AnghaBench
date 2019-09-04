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
struct strlist {scalar_t__ file_only; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ asprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int strlist__add (struct strlist*,char const*) ; 
 int strlist__load (struct strlist*,char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int strlist__parse_list_entry(struct strlist *slist, const char *s,
				     const char *subst_dir)
{
	int err;
	char *subst = NULL;

	if (strncmp(s, "file://", 7) == 0)
		return strlist__load(slist, s + 7);

	if (subst_dir) {
		err = -ENOMEM;
		if (asprintf(&subst, "%s/%s", subst_dir, s) < 0)
			goto out;

		if (access(subst, F_OK) == 0) {
			err = strlist__load(slist, subst);
			goto out;
		}

		if (slist->file_only) {
			err = -ENOENT;
			goto out;
		}
	}

	err = strlist__add(slist, s);
out:
	free(subst);
	return err;
}