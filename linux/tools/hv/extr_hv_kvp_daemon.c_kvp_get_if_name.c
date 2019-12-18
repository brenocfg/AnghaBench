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
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  dev_id ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 char* KVP_NET_DIR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char* fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *kvp_get_if_name(char *guid)
{
	DIR *dir;
	struct dirent *entry;
	FILE    *file;
	char    *p, *x;
	char    *if_name = NULL;
	char    buf[256];
	char dev_id[PATH_MAX];

	dir = opendir(KVP_NET_DIR);
	if (dir == NULL)
		return NULL;

	while ((entry = readdir(dir)) != NULL) {
		/*
		 * Set the state for the next pass.
		 */
		snprintf(dev_id, sizeof(dev_id), "%s%s/device/device_id",
			 KVP_NET_DIR, entry->d_name);

		file = fopen(dev_id, "r");
		if (file == NULL)
			continue;

		p = fgets(buf, sizeof(buf), file);
		if (p) {
			x = strchr(p, '\n');
			if (x)
				*x = '\0';

			if (!strcmp(p, guid)) {
				/*
				 * Found the guid match; return the interface
				 * name. The caller will free the memory.
				 */
				if_name = strdup(entry->d_name);
				fclose(file);
				break;
			}
		}
		fclose(file);
	}

	closedir(dir);
	return if_name;
}