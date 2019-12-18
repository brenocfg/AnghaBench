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
struct key_value_s {char* value; int /*<<< orphan*/  key; struct key_value_s* next; } ;
struct fpm_worker_pool_s {char* user; char* home; TYPE_1__* config; } ;
struct TYPE_2__ {struct key_value_s* env; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 

__attribute__((used)) static int fpm_env_conf_wp(struct fpm_worker_pool_s *wp) /* {{{ */
{
	struct key_value_s *kv;

	for (kv = wp->config->env; kv; kv = kv->next) {
		if (*kv->value == '$') {
			char *value = getenv(kv->value + 1);

			if (!value) {
				value = "";
			}

			free(kv->value);
			kv->value = strdup(value);
		}

		/* autodetected values should be removed
			if these vars specified in config */
		if (!strcmp(kv->key, "USER")) {
			free(wp->user);
			wp->user = 0;
		}

		if (!strcmp(kv->key, "HOME")) {
			free(wp->home);
			wp->home = 0;
		}
	}

	return 0;
}