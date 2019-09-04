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
struct stat {scalar_t__ st_size; } ;
struct TYPE_2__ {char* path; } ;
struct perf_data {TYPE_1__ file; } ;
typedef  int /*<<< orphan*/  oldname ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int check_backup(struct perf_data *data)
{
	struct stat st;

	if (!stat(data->file.path, &st) && st.st_size) {
		/* TODO check errors properly */
		char oldname[PATH_MAX];
		snprintf(oldname, sizeof(oldname), "%s.old",
			 data->file.path);
		unlink(oldname);
		rename(data->file.path, oldname);
	}

	return 0;
}