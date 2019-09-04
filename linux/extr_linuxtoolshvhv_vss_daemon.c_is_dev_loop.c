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
struct dirent {char* d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int R_OK ; 
 int X_OK ; 
 int /*<<< orphan*/  access (char*,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool is_dev_loop(const char *blkname)
{
	char *buffer;
	DIR *dir;
	struct dirent *entry;
	bool ret = false;

	buffer = malloc(PATH_MAX);
	if (!buffer) {
		syslog(LOG_ERR, "Can't allocate memory!");
		exit(1);
	}

	snprintf(buffer, PATH_MAX, "%s/loop", blkname);
	if (!access(buffer, R_OK | X_OK)) {
		ret = true;
		goto free_buffer;
	} else if (errno != ENOENT) {
		syslog(LOG_ERR, "Can't access: %s; error:%d %s!",
		       buffer, errno, strerror(errno));
	}

	snprintf(buffer, PATH_MAX, "%s/slaves", blkname);
	dir = opendir(buffer);
	if (!dir) {
		if (errno != ENOENT)
			syslog(LOG_ERR, "Can't opendir: %s; error:%d %s!",
			       buffer, errno, strerror(errno));
		goto free_buffer;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 ||
		    strcmp(entry->d_name, "..") == 0)
			continue;

		snprintf(buffer, PATH_MAX, "%s/slaves/%s", blkname,
			 entry->d_name);
		if (is_dev_loop(buffer)) {
			ret = true;
			break;
		}
	}
	closedir(dir);
free_buffer:
	free(buffer);
	return ret;
}