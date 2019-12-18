#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  st_mode; } ;
typedef  TYPE_1__ zend_stat_t ;
struct TYPE_5__ {char* executable_location; } ;
typedef  char* PG ;

/* Variables and functions */
 scalar_t__ GetModuleFileName (int /*<<< orphan*/ ,char*,int) ; 
 int MAXPATHLEN ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ VCWD_ACCESS (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VCWD_REALPATH (char*,char*) ; 
 scalar_t__ VCWD_STAT (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  X_OK ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 scalar_t__ malloc (int) ; 
 char* php_strtok_r (char*,char*,char**) ; 
 TYPE_2__ sapi_module ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strchr (char*,char) ; 

__attribute__((used)) static void php_binary_init(void)
{
	char *binary_location = NULL;
#ifdef PHP_WIN32
	binary_location = (char *)malloc(MAXPATHLEN);
	if (binary_location && GetModuleFileName(0, binary_location, MAXPATHLEN) == 0) {
		free(binary_location);
		PG(php_binary) = NULL;
	}
#else
	if (sapi_module.executable_location) {
		binary_location = (char *)malloc(MAXPATHLEN);
		if (binary_location && !strchr(sapi_module.executable_location, '/')) {
			char *envpath, *path;
			int found = 0;

			if ((envpath = getenv("PATH")) != NULL) {
				char *search_dir, search_path[MAXPATHLEN];
				char *last = NULL;
				zend_stat_t s;

				path = estrdup(envpath);
				search_dir = php_strtok_r(path, ":", &last);

				while (search_dir) {
					snprintf(search_path, MAXPATHLEN, "%s/%s", search_dir, sapi_module.executable_location);
					if (VCWD_REALPATH(search_path, binary_location) && !VCWD_ACCESS(binary_location, X_OK) && VCWD_STAT(binary_location, &s) == 0 && S_ISREG(s.st_mode)) {
						found = 1;
						break;
					}
					search_dir = php_strtok_r(NULL, ":", &last);
				}
				efree(path);
			}
			if (!found) {
				free(binary_location);
				binary_location = NULL;
			}
		} else if (!VCWD_REALPATH(sapi_module.executable_location, binary_location) || VCWD_ACCESS(binary_location, X_OK)) {
			free(binary_location);
			binary_location = NULL;
		}
	}
#endif
	PG(php_binary) = binary_location;
}