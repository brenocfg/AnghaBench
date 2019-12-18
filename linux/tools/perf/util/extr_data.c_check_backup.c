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
struct stat {scalar_t__ st_size; } ;
struct perf_data {char* path; } ;
typedef  int /*<<< orphan*/  oldname ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ perf_data__is_read (struct perf_data*) ; 
 int /*<<< orphan*/  pr_err (char*,char*,char*,...) ; 
 scalar_t__ rename (char*,char*) ; 
 int rm_rf_perf_data (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_backup(struct perf_data *data)
{
	struct stat st;

	if (perf_data__is_read(data))
		return 0;

	if (!stat(data->path, &st) && st.st_size) {
		char oldname[PATH_MAX];
		int ret;

		snprintf(oldname, sizeof(oldname), "%s.old",
			 data->path);

		ret = rm_rf_perf_data(oldname);
		if (ret) {
			pr_err("Can't remove old data: %s (%s)\n",
			       ret == -2 ?
			       "Unknown file found" : strerror(errno),
			       oldname);
			return -1;
		}

		if (rename(data->path, oldname)) {
			pr_err("Can't move data: %s (%s to %s)\n",
			       strerror(errno),
			       data->path, oldname);
			return -1;
		}
	}

	return 0;
}