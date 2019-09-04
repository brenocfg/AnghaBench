#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpm_worker_pool_s {TYPE_1__* config; } ;
struct TYPE_4__ {char* prefix; } ;
struct TYPE_3__ {char* prefix; } ;

/* Variables and functions */
 char* PHP_PREFIX ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  efree (char*) ; 
 TYPE_2__ fpm_globals ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fpm_evaluate_full_path(char **path, struct fpm_worker_pool_s *wp, char *default_prefix, int expand) /* {{{ */
{
	char *prefix = NULL;
	char *full_path;

	if (!path || !*path || **path == '/') {
		return 0;
	}

	if (wp && wp->config) {
		prefix = wp->config->prefix;
	}

	/* if the wp prefix is not set */
	if (prefix == NULL) {
		prefix = fpm_globals.prefix;
	}

	/* if the global prefix is not set */
	if (prefix == NULL) {
		prefix = default_prefix ? default_prefix : PHP_PREFIX;
	}

	if (expand) {
		char *tmp;
		tmp = strstr(*path, "$prefix");
		if (tmp != NULL) {

			if (tmp != *path) {
				zlog(ZLOG_ERROR, "'$prefix' must be use at the beginning of the value");
				return -1;
			}

			if (strlen(*path) > strlen("$prefix")) {
				free(*path);
				tmp = strdup((*path) + strlen("$prefix"));
				*path = tmp;
			} else {
				free(*path);
				*path = NULL;
			}
		}
	}

	if (*path) {
		spprintf(&full_path, 0, "%s/%s", prefix, *path);
		free(*path);
		*path = strdup(full_path);
		efree(full_path);
	} else {
		*path = strdup(prefix);
	}

	if (**path != '/' && wp != NULL && wp->config) {
		return fpm_evaluate_full_path(path, NULL, default_prefix, expand);
	}
	return 0;
}