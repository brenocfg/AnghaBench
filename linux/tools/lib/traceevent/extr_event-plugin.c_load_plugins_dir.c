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
struct tep_handle {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
load_plugins_dir(struct tep_handle *tep, const char *suffix,
		 const char *path,
		 void (*load_plugin)(struct tep_handle *tep,
				     const char *path,
				     const char *name,
				     void *data),
		 void *data)
{
	struct dirent *dent;
	struct stat st;
	DIR *dir;
	int ret;

	ret = stat(path, &st);
	if (ret < 0)
		return;

	if (!S_ISDIR(st.st_mode))
		return;

	dir = opendir(path);
	if (!dir)
		return;

	while ((dent = readdir(dir))) {
		const char *name = dent->d_name;

		if (strcmp(name, ".") == 0 ||
		    strcmp(name, "..") == 0)
			continue;

		/* Only load plugins that end in suffix */
		if (strcmp(name + (strlen(name) - strlen(suffix)), suffix) != 0)
			continue;

		load_plugin(tep, path, name, data);
	}

	closedir(dir);
}