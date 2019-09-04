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
struct path {int /*<<< orphan*/  dentry; } ;

/* Variables and functions */
 scalar_t__ d_unlinked (int /*<<< orphan*/ ) ; 
 int prepend (char**,int*,char*,int) ; 
 int prepend_path (struct path const*,struct path const*,char**,int*) ; 

__attribute__((used)) static int path_with_deleted(const struct path *path,
			     const struct path *root,
			     char **buf, int *buflen)
{
	prepend(buf, buflen, "\0", 1);
	if (d_unlinked(path->dentry)) {
		int error = prepend(buf, buflen, " (deleted)", 10);
		if (error)
			return error;
	}

	return prepend_path(path, root, buf, buflen);
}