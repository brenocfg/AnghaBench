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
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_mode; } ;
struct perf_data_file {int fd; int /*<<< orphan*/  size; int /*<<< orphan*/  path; } ;
struct TYPE_2__ {scalar_t__ version; int nr; struct perf_data_file* files; } ;
struct perf_data {char* path; TYPE_1__ dir; int /*<<< orphan*/  is_dir; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 scalar_t__ PERF_DIR_VERSION ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  close_dir (struct perf_data_file*,int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 struct perf_data_file* realloc (struct perf_data_file*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

int perf_data__open_dir(struct perf_data *data)
{
	struct perf_data_file *files = NULL;
	struct dirent *dent;
	int ret = -1;
	DIR *dir;
	int nr = 0;

	if (WARN_ON(!data->is_dir))
		return -EINVAL;

	/* The version is provided by DIR_FORMAT feature. */
	if (WARN_ON(data->dir.version != PERF_DIR_VERSION))
		return -1;

	dir = opendir(data->path);
	if (!dir)
		return -EINVAL;

	while ((dent = readdir(dir)) != NULL) {
		struct perf_data_file *file;
		char path[PATH_MAX];
		struct stat st;

		snprintf(path, sizeof(path), "%s/%s", data->path, dent->d_name);
		if (stat(path, &st))
			continue;

		if (!S_ISREG(st.st_mode) || strncmp(dent->d_name, "data", 4))
			continue;

		ret = -ENOMEM;

		file = realloc(files, (nr + 1) * sizeof(*files));
		if (!file)
			goto out_err;

		files = file;
		file = &files[nr++];

		file->path = strdup(path);
		if (!file->path)
			goto out_err;

		ret = open(file->path, O_RDONLY);
		if (ret < 0)
			goto out_err;

		file->fd = ret;
		file->size = st.st_size;
	}

	if (!files)
		return -EINVAL;

	data->dir.files = files;
	data->dir.nr    = nr;
	return 0;

out_err:
	close_dir(files, nr);
	return ret;
}