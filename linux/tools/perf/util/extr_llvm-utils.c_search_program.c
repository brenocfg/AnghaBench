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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int PATH_MAX ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  scnprintf (char*,int,char*,char*,char const*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int
search_program(const char *def, const char *name,
	       char *output)
{
	char *env, *path, *tmp = NULL;
	char buf[PATH_MAX];
	int ret;

	output[0] = '\0';
	if (def && def[0] != '\0') {
		if (def[0] == '/') {
			if (access(def, F_OK) == 0) {
				strlcpy(output, def, PATH_MAX);
				return 0;
			}
		} else if (def[0] != '\0')
			name = def;
	}

	env = getenv("PATH");
	if (!env)
		return -1;
	env = strdup(env);
	if (!env)
		return -1;

	ret = -ENOENT;
	path = strtok_r(env, ":",  &tmp);
	while (path) {
		scnprintf(buf, sizeof(buf), "%s/%s", path, name);
		if (access(buf, F_OK) == 0) {
			strlcpy(output, buf, PATH_MAX);
			ret = 0;
			break;
		}
		path = strtok_r(NULL, ":", &tmp);
	}

	free(env);
	return ret;
}