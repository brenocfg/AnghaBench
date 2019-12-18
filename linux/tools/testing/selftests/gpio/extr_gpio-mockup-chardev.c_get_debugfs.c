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
struct libmnt_table {int dummy; } ;
struct libmnt_iter {int dummy; } ;
struct libmnt_fs {int dummy; } ;
struct libmnt_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  MNT_ITER_FORWARD ; 
 int asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mnt_context_get_mtab (struct libmnt_context*,struct libmnt_table**) ; 
 int /*<<< orphan*/  mnt_free_context (struct libmnt_context*) ; 
 int /*<<< orphan*/  mnt_free_iter (struct libmnt_iter*) ; 
 char* mnt_fs_get_fstype (struct libmnt_fs*) ; 
 int /*<<< orphan*/  mnt_fs_get_target (struct libmnt_fs*) ; 
 struct libmnt_context* mnt_new_context () ; 
 struct libmnt_iter* mnt_new_iter (int /*<<< orphan*/ ) ; 
 scalar_t__ mnt_table_next_fs (struct libmnt_table*,struct libmnt_iter*,struct libmnt_fs**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int get_debugfs(char **path)
{
	struct libmnt_context *cxt;
	struct libmnt_table *tb;
	struct libmnt_iter *itr = NULL;
	struct libmnt_fs *fs;
	int found = 0, ret;

	cxt = mnt_new_context();
	if (!cxt)
		err(EXIT_FAILURE, "libmount context allocation failed");

	itr = mnt_new_iter(MNT_ITER_FORWARD);
	if (!itr)
		err(EXIT_FAILURE, "failed to initialize libmount iterator");

	if (mnt_context_get_mtab(cxt, &tb))
		err(EXIT_FAILURE, "failed to read mtab");

	while (mnt_table_next_fs(tb, itr, &fs) == 0) {
		const char *type = mnt_fs_get_fstype(fs);

		if (!strcmp(type, "debugfs")) {
			found = 1;
			break;
		}
	}
	if (found) {
		ret = asprintf(path, "%s/gpio", mnt_fs_get_target(fs));
		if (ret < 0)
			err(EXIT_FAILURE, "failed to format string");
	}

	mnt_free_iter(itr);
	mnt_free_context(cxt);

	if (!found)
		return -1;

	return 0;
}