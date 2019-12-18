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
struct TYPE_4__ {TYPE_1__* config; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_2__* current_wp ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  spprintf (char**,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static int fpm_conf_expand_pool_name(char **value) {
	char *token;

	if (!value || !*value) {
		return 0;
	}

	while (*value && (token = strstr(*value, "$pool"))) {
		char *buf;
		char *p2 = token + strlen("$pool");

		/* If we are not in a pool, we cannot expand this name now */
		if (!current_wp || !current_wp->config  || !current_wp->config->name) {
			return -1;
		}

		/* "aaa$poolbbb" becomes "aaa\0oolbbb" */
		token[0] = '\0';

		/* Build a brand new string with the expanded token */
		spprintf(&buf, 0, "%s%s%s", *value, current_wp->config->name, p2);

		/* Free the previous value and save the new one */
		free(*value);
		*value = strdup(buf);
		efree(buf);
	}

	return 0;
}