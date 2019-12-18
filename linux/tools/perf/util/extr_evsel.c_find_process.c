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
struct dirent {scalar_t__ d_type; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_DIR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ filename__read_str (char*,char**,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs__mountpoint () ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 int strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static bool find_process(const char *name)
{
	size_t len = strlen(name);
	DIR *dir;
	struct dirent *d;
	int ret = -1;

	dir = opendir(procfs__mountpoint());
	if (!dir)
		return false;

	/* Walk through the directory. */
	while (ret && (d = readdir(dir)) != NULL) {
		char path[PATH_MAX];
		char *data;
		size_t size;

		if ((d->d_type != DT_DIR) ||
		     !strcmp(".", d->d_name) ||
		     !strcmp("..", d->d_name))
			continue;

		scnprintf(path, sizeof(path), "%s/%s/comm",
			  procfs__mountpoint(), d->d_name);

		if (filename__read_str(path, &data, &size))
			continue;

		ret = strncmp(name, data, len);
		free(data);
	}

	closedir(dir);
	return ret ? false : true;
}